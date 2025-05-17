#ifndef PREPAYMENTMANAGEMENT_H
#define PREPAYMENTMANAGEMENT_H

#include "Bank.hpp"
#include <string>

using namespace std;

class PrePaymentManagement {
private:

public:
    // 생성자
    PaymentManagement();

    // 메서드
    void requestPrePayment(std::string dvmId, AuthCode authCode); // 선결제 요청
    void acceptPrePayment(AuthCode authCode); // 선결제 수락
};

#endif // PREPAYMENTMANAGEMENT_H