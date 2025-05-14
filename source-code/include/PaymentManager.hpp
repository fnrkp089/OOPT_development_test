#ifndef PAYMENTMANAGEMENT_HPP
#define PAYMENTMANAGEMENT_HPP

#include "Bank.hpp"
#include <string>

using namespace std;

class PaymentManagement {
private:
    string pmId;

public:
    // 생성자
    PaymentManagement();

    // 카드번호를 가져오는 메서드
    string getCardNum();

    // 결제를 요청하는 메서드 (카드번호를 내부적으로 호출해서 사용)
    // 1: 성공, 2: 카드 정보 안 맞음, 3: 계좌에 돈이 부족함, -1: 예외상황 발생ㄱ
    int requestPayment(int cost);
};

#endif // PAYMENTMANAGEMENT_HPP