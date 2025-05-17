#ifndef DVM_H
#define DVM_H

#include "ItemManager.hpp"
#include "PaymentManager.hpp"
#include "AuthCodeManager.hpp"
#include <string>
#include <algorithm>

using namespace std;

class DVM {
private:
    string DVMId;
    int coorX;
    int coorY;

public:
    DVM(const string& id, int x, int y);
    string askUserPrepayment();
    pair<int, int> requestSelect();
    void showPaymentResult(int payResult);
    void showPrepaymentResult(const AuthCode& authCode);

    // 추가 메서드
    bool askBuyOrCodeInput();
    string requestAuthCode();
};

#endif // DVM_H