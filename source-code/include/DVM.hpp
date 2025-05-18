#ifndef DVM_H
#define DVM_H

#include "ItemManager.hpp"
#include "PaymentManager.hpp"
#include "AuthCodeManager.hpp"
#include "MsgManager.hpp"
#include "AltDVMManager.hpp"
#include <string>
#include <algorithm>


class DVM {
private:
    std::string DVMId;
    int coorX;
    int coorY;

public:
    DVM(const std::string& id, int x, int y);
    std::string askUserPrepayment();
    std::pair<int, int> requestSelect();
    void showPaymentResult(int payResult);
    void showPrepaymentResult(const std::string authCode, std::pair<int,int> location);

    // 추가 메서드
    bool askBuyOrCodeInput();
    std::string requestAuthCode();
};

#endif // DVM_H