#include "DVM.hpp"
#include <iostream>
#include <algorithm>
#include <winsock2.h>

using namespace std;

/** ---- 실행흐름 ----
 * -- 일반적인 음료수 구매 흐름 --
 * 메뉴 출력 -> 메뉴 선택 -> 재고 확인
 * -> (재고가 충분한 경우) -> 결제 요청
 *                    -> (결제 성공한 경우) -> 재고 감소 -> 구매 결과 출력 -> 종료
 *                    -> (결제 실패한 경우) -> 실패 이유 출력 -> 종료
 * -> (재고가 부족한 경우) -> 대안 자판기 탐색 -> 선결제 여부 확인
 *                    -> (선결제 O) -> 인증코드 생성 -> 대안자판기에게 전달
 *                    -> (선결제 X) -> 대안 자판기 위치 출력
 * 
 * -- 사용자가 선결제 코드를 입력 했을때 --
 * 인증코드 입력 -> 인증코드 확인 -> 인증코드 객체에 담겨있는 정보로 음료수 제공
 */
DVM::DVM(const string& id, int x, int y, int port)
    : DVMId(id), coorX(x), coorY(y), port(port),
        msgManager(&itemManager, &authCodeManager, &altDVMManager, &p2pClient, id),
        p2pServer(port, [this](const std::string& msg){ return msgManager.receive(msg); }) {
    WSAData wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
    }
    p2pServer.start();
}

DVM::~DVM() {
    p2pServer.stop();
    WSACleanup();
}

void DVM::run() {
    if (askBuyOrCodeInput()) {
        handleBuyFlow();
    } else {
        handleAuthCodeFlow();
    }
}

// 음료수 구매 로직
void DVM::handleBuyFlow() {
    itemManager.showItemList();
    itemManager.saveSelectedItem(requestSelect());

    // 음료수가 충분한 경우
    if (itemManager.isEnough()) {
        int payResult = paymentManager.requestPayment(itemManager.getPaymentAmount());
        showPaymentResult(payResult);

        // 결제 성공
        if (payResult == 1) {
            itemManager.minusStock();
            itemManager.showBuyResult();
        }
    // 재고가 부족한 경우
    } else {
        string tempMsg = msgManager.createRequestItemStockAndLocation(
            to_string(itemManager.getSelectedItemId()),
            itemManager.getSelectedItemNum());

        for (const auto& dvm : altDVMManager.getAltDVMList()) {
            msgManager.sendTo(dvm.getId(), tempMsg);
        }

        altDVMManager.selectAltDVM(coorX, coorY);

        // 선결제 원하는 경우
        if (askUserPrepayment() == "y") {
            string authCode = authCodeManager.generateCode();
            string dvmID = altDVMManager.getSelectedDVM();

            // if(msgManager.receive())
            int payResult = paymentManager.requestPayment(itemManager.getPaymentAmount());
            showPaymentResult(payResult);

            // 결제 성공
            if (payResult == 1) {
                showPrepaymentResult(authCode, altDVMManager.getAltDVMLocation());
            }
        // 선결제 원하지 않는 경우
        } else {
            showPrepaymentResult("noprepayment", altDVMManager.getAltDVMLocation());
        }
    }
}

// 인증코드 처리 로직
void DVM::handleAuthCodeFlow() {
    string code = requestAuthCode();

    if (authCodeManager.isValidAuthCode(code)) {
        itemManager.saveSelectedItem(authCodeManager.popAuthCode(code));
        itemManager.showBuyResult();
    } else {
        cout << "해당 인증코드가 존재하지 않습니다." << endl;
    }
}

// 구매 방식 요청 로직
bool DVM::askBuyOrCodeInput() {
    string answer;
    while (true) {
        cout << "음료수 구매(1) | 인증코드 입력(2): ";
        cin >> answer;
        if (answer == "1" || answer == "2") break;
        cout << "1 또는 2로 입력해주세요." << endl;
    }
    return answer == "1";
}

// 선결제 의사 확인 로직
string DVM::askUserPrepayment() {
    string answer;
    while (true) {
        cout << "선결제 하시겠습니까? Yes(Y|y) No(N|n): ";
        cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if (answer == "y" || answer == "n") break;
        cout << "Y|y 또는 N|n으로 입력해주세요." << endl;
    }
    return answer;
}

// 음료수 선택 요청 로직
pair<int, int> DVM::requestSelect() {
    int itemId, quantity;
    while (true) {
        cout << "음료수 번호를 입력해주세요: ";
        cin >> itemId;
        if (itemId >= 1 && itemId <= 20) break;
        cout << "음료수 번호는 1 ~ 20 사이의 값입니다." << endl;
    }

    while (true) {
        cout << "수량을 입력해주세요: ";
        cin >> quantity;
        if (quantity >= 1 && quantity <= 99) break;
        cout << "음료수 수량은 1~99 까지만 선택 가능합니다." << endl;
    }

    return {itemId, quantity};
}

// 결제 결과 표시 로직
void DVM::showPaymentResult(int payResult) {
    switch (payResult) {
        case 1: cout << "결제 성공하였습니다." << endl; break;
        case 2: cout << "카드 정보가 불일치합니다." << endl; break;
        case 3: cout << "계좌에 돈이 부족합니다." << endl; break;
        default: cout << "알 수 없는 오류가 발생했습니다." << endl; break;
    }
}

// 선결제 결과 표시 로직
void DVM::showPrepaymentResult(const string& authCode, pair<int, int> location) {
    if (authCode != "noprepayment") {
        cout << "인증코드는 " << authCode << "입니다." << endl;
    }

    if (location.first == -1) {
        cout << "대안자판기가 없습니다." << endl;
    } else {
        cout << "대안 자판기의 위치는 " << location.first << ", " << location.second << " 입니다." << endl;
    }
}

// 인증코드 입력 요청 로직
string DVM::requestAuthCode() {
    string code;
    while (true) {
        cout << "인증코드를 입력해주세요(5자리): ";
        cin >> code;
        if (code.length() == 5) break;
        cout << "5자리 인증코드를 입력해주세요." << endl;
    }
    return code;
}

pair<int, int> DVM::getDVMLocation()
{
    return {coorX,coorY};
}
