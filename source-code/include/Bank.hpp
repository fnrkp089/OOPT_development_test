#ifndef BANK_HPP
#define BANK_HPP

#include <string>

using namespace std;

class Bank {
private:
    string bankId;

public:
    // 생성자
    Bank();

    // 결제 메서드
    int pay(string cardNum, int cost);
};

#endif // BANK_HPP