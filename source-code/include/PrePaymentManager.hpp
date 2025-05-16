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

    // 선결제 요청
    requestPrePayment(std::string dvmId, AuthCode authCode);

    // 선결제 수락
    acceptPrePayment(AuthCode authCode);
};

#endif // PREPAYMENTMANAGEMENT_H