#include "PaymentManager.hpp"
#include <iostream>

PaymentManagement::PaymentManagement() : pmId("temp") {
}

string PaymentManagement::getCardNum() {
    string cardNum;
    cout << "카드 번호를 입력해주세요(5자리): ";
    cin >> cardNum;
    // TODO: 입력예외처리
    return cardNum;
}

// 1: 성공, 2: 카드 정보 안 맞음, 3: 계좌에 돈이 부족함, -1: 예외상황 발생
int PaymentManagement::requestPayment(int cost) {
    Bank bank;
    return bank.pay(getCardNum(), cost);
}