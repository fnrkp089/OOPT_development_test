#ifndef PrePaymentManager_H
#define PrePaymentManager_H

#include "Bank.hpp"
#include "AuthCodeManager.hpp"
#include <string>

using namespace std;

class PrePaymentManager {
private:

public:
    // 생성자
    PrePaymentManager();

    // 메서드
    void requestPrePayment(std::string dvmId, const AuthCode& authCode); // 선결제 요청
    void acceptPrePayment(const AuthCode& authCode); // 선결제 수락
};

#endif // PrePaymentManager_H