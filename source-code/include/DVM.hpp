#ifndef DVM_H
#define DVM_H

#include "ItemManager.hpp"
#include "PaymentManager.hpp"
#include <string>
//#include "AuthCode.h"

using namespace std;

class DVM {
private:
    string DVMId;
    int coorX;
    int coorY;

public:
    // 생성자
    DVM(const string& id, int x, int y);

    // 메서드 선언
    string askUserPrepayment();
    pair<int, int> requestSelect();
    int showPaymentResult(int payResult);
    //void showPrepaymentResult(const AuthCode& authCode);
};

#endif // DVM_H