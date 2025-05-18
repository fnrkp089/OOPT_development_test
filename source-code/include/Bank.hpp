#ifndef BANK_HPP
#define BANK_HPP

#include <string>
#include <map>

class Bank {
private:
    std::string bankId;
    map<std::string, int> account;
public:
    // 생성자
    Bank();

    // 결제 메서드
    int pay(std::string cardNum, int cost);
};

#endif // BANK_HPP