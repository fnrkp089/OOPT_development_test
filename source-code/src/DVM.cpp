#include "DVM.hpp"
#include <iostream>

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
DVM::DVM(const string& id, int x, int y)
    : DVMId(id), coorX(x), coorY(y), ItemManager(), authCodeManager(), 
    altDVMManager(ItemManager), msgManager(ItemManager, authCodeManager, altDVMManager, DVMId) {
        bool buyOrCodeInput = askBuyOrCodeInput();
        // 음료수 구매
        if(buyOrCodeInput){
            itemManager.showItemList();
            itemManager.saveSelectedItem(requestSelect());
            // 재고가 충분한 경우
            if(itemManager.isEnough()){
                PaymentManager pm;
                int payResult = pm.requestPayment(itemManager.getPaymentAmount());
                showPaymentResult(payResult);
                // 결제 성공한 경우
                if(payResult == 1){
                    itemManager.minusStock();
                    itemManager.showBuyResult();
                }
                // 결제 실패한 경우
                else return;
            }
            // 재고가 부족한 경우
            else{
                msgManager.requestItemStockAndLocation();
                // 선결제 O
                if(askUserPrepayment().compare("y") == 0){
                    string authCode = authCodeManager.generateCode();
                    string dvmID = altDVMManager.getSelectedDVM();
                    altDVMMsgManager.requestPrepayment(dvmID, authCodeManager.makeAuthCode(authCode, itemManager.getselectedItemId(),itemManager.getselectedItemNum()));
                    showPrepaymentResult(authCode, altDVMManager.getAltDVMLocation());
                }
                // 선결제 X
                else{
                    string authCode = "noprepayment";
                    showPrepaymentResult(authCode, altDVMManager.getAltDVMLocation());
                }
            }
        }
        // 인증코드 입력
        else{
            const string code = requestAuthCode();
            // 인증코드 확인
            if(authCodeManager.isValidAuthCode(code)) {
                itemManager.saveSelectedItem(authCodeManager.popAuthCode(code));
            } else {
                cout << "해당 인증코드가 존재하지 않습니다." << endl;
                return;
            }
            // 인증코드 객체에 담겨있는 정보로 음료수 제공
            itemManager.showBuyResult();
        }

    }

// 선결제 여부 묻기
// 음료수의 재고가 부족할 때
string DVM::askUserPrepayment() {
    string answer;
    bool isAvailable = false;
    while(!isAvailable){
        cout << "선결제 하시겠습니까? Yes(Y|y) No(N|n): ";
        cin >> answer;
        transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
        if(answer.compare("y") == 0 || answer.compare("n") == 0){
            isAvailable = true;
        }
        else {
            cout << "Y|y 또는 N|n으로 입력해주세요." << endl;
        }
    }
    return answer;
}

// 항목 선택 요청
pair<int,int> DVM::requestSelect() {
    pair<int,int> answer;
    bool isAvailable = false;

    while(!isAvailable){
        cout << "음료수 번호를 입력해주세요: ";
        cin >> answer.first;
        if(answer.first <= 20 && answer.first >= 1){
            isAvailable = true;
        }
        else{
            cout << "음료수 번호는 1 ~ 20 사이의 값입니다." << endl;
        }
    }
    isAvailable = false;

    while(!isAvailable){
        cout << "수량을 입력해주세요: ";
        cin >> answer.second;
        if(answer.second <= 99 && answer.second >= 1){
            isAvailable = true;
        }
        else{
            cout << "음료수 수량은 1~99 까지만 선택 가능합니다." << endl;
        }
    }
    return answer;
}

// 결제 결과 출력
void DVM::showPaymentResult(int payResult) {
    switch (payResult) {
        case 1:
            cout << "결제 성공하였습니다." << endl;
            break;
        case 2:
            cout << "카드 정보가 불일치합니다." << endl;
            break;
        case 3:
            cout << "계좌에 돈이 부족합니다." << endl;
            break;
        default:
            cout << "알 수 없는 오류가 발생했습니다." << endl;
            break;
    }
}

// 선결제 결과 출력
void DVM::showPrepaymentResult(const string authCode, pair<int,int> location) {
    // 선결제 O
    if(authCode.compare("noprepayment")!=0){
        cout << "인증코드는 " << authCode << "입니다." << endl;
        if(location.first == -1) cout << "대안자판기가 없습니다." << endl;
        else cout << "대안 자판기의 위치는 " << location.first << "," << location.second << " 입니다." << endl;
    }
    // 선결제 X
    else{
        if(location.first == -1) cout << "대안자판기가 없습니다." << endl;
        else cout << "대안 자판기의 위치는 " << location.first << "," << location.second << " 입니다." << endl;
    }
}

// 음료수 구매일 경우 true 반환
bool DVM::askBuyOrCodeInput(){
    string answer;
    bool isAvailable = false;
    while(!isAvailable){
        cout << "음료수 구매(1) | 인증코드 입력(2): ";
        cin >> answer;
        if(answer.compare("1") == 0 || answer.compare("2") == 0){
            isAvailable = true;
        }
        else {
            cout << "1 또는 2로 입력해주세요." << endl;
        }
    }
    return answer.compare("1") == 0;
}

string DVM::requestAuthCode(){
    string answer;
    bool isAvailable = false;
    while(!isAvailable){
        cout << "인증코드를 입력해주세요(5자리):  ";
        cin >> answer;
        if(answer.length()==5){
            isAvailable = true;
        }
        else {
            cout << "5자리 인증코드를 입력해주세요." << endl;
        }
    }
    return answer;
}

