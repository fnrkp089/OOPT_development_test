#include "DVM.hpp"
#include <iostream>

/** ---- 실행흐름 ----
 * 메뉴 출력 -> 메뉴 선택 -> 재고 확인
 * -> (재고가 충분한 경우) -> 결제 요청
 *                    -> (결제 성공한 경우) -> 재고 감소 -> 구매 결과 출력 -> 종료
 *                    -> (결제 실패한 경우) -> 실패 이유 출력 -> 종료
 * -> (재고가 부족한 경우) -> 선결제 여부 확인
 *                    -> (선결제 O)
 *                    -> (선결제 X)
 */
DVM::DVM(const std::string& id, int x, int y)
    : DVMId(id), coorX(x), coorY(y) {
        ItemManager itemManager;
        itemManager.showItemList();
        itemManager.saveSelectedItem(requestSelect());
        // 재고가 충분한 경우
        if(itemManager.isEnough()){
            PaymentManagement pm;
            // 결제 성공한 경우
            if(showPaymentResult(pm.requestPayment(itemManager.getPaymentAmount())) == 1){
                itemManager.minusStock();
                itemManager.showBuyResult();
            }
            // 결제 실패한 경우
            else return;
        }
        // 재고가 부족한 경우
        else{
            // 선결제 O
            if(askUserPrepayment().compare("y") == 0){
                // TODO: 선결제 O
                // test code
                cout << "선결제 합니다" << endl;
            }
            // 선결제 X
            else{
                // TODO: 선결제 x
                // test code
                cout << "선결제 안합니다" << endl;
            }
        }
    }

// 선결제 여부 묻기
// 음료수의 재고가 부족할 때
string DVM::askUserPrepayment() {
    string answer;
    cout << "선결제 하시겠습니까? Yes(y) No(n): ";
    cin >> answer;
    // TODO: 입력 예외 처리
    return answer;
}

// 항목 선택 요청
pair<int,int> DVM::requestSelect() {
    pair<int,int> answer;
    cout << "음료수 번호를 입력해주세요: ";
    cin >> answer.first;
    cout << "수량을 입력해주세요: ";
    cin >> answer.second;
    // TODO: 입력 예외 처리
    return answer;
}

// 결제 결과 출력
int DVM::showPaymentResult(int payResult) {
    switch (payResult) {
        case 1:
            std::cout << "결제 성공하였습니다." << std::endl;
            break;
        case 2:
            std::cout << "카드 정보가 불일치합니다." << std::endl;
            break;
        case 3:
            std::cout << "계좌에 돈이 부족합니다." << std::endl;
            break;
        default:
            std::cout << "알 수 없는 오류가 발생했습니다." << std::endl;
            break;
    }
    return payResult;
}

// // 선결제 결과 출력
// void DVM::showPrepaymentResult(const AuthCode& authCode) {
//     // TODO: 인증 코드 및 상태 출력
// }