#include "DVM.hpp"
#include <iostream>

// 생성자 정의
DVM::DVM(const std::string& id, int x, int y)
    : DVMId(id), coorX(x), coorY(y) {
        ItemManager itemManager;
        itemManager.showItemList();
        itemManager.saveSelectedItem(requestSelect());
        if(itemManager.isEnough()){
            // TODO: 재고가 충분한 경우
            PaymentManagement pm;
            pm.requestPayment(itemManager.getPaymentAmount());
            // test code
            cout << "재고가 충분하므로 결제 진행합니다" << endl;
            
        }
        else{
            if(askUserPrepayment().compare("y") == 0){
                // TODO: 선결제 O
                // test code
                cout << "선결제 할게용" << endl;
            }
            else{
                // TODO: 선결제 x
                // test code
                cout << "선결제 안할게용" << endl;
            }
        }
        itemManager.showBuyResult();
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
void DVM::showPaymentResult(int payResult) {
    // TODO: 결제 성공/실패 출력
}

// // 선결제 결과 출력
// void DVM::showPrepaymentResult(const AuthCode& authCode) {
//     // TODO: 인증 코드 및 상태 출력
// }