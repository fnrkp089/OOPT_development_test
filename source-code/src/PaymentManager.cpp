#include "PaymentManager.hpp"
#include <iostream>

PaymentManagement::PaymentManagement() : pmId("temp") {
}

string PaymentManagement::getCardNum() {
    string cardNum;
    cout << "카드 번호를 입력해주세요: ";
    cin >> cardNum;
    // TODO: 입력예외처리
    return cardNum;
}

int PaymentManagement::requestPayment(int cost) {
    Bank bank;
    return bank.pay(getCardNum(), cost);
}