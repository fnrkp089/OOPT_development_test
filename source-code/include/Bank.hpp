#ifndef BANK_HPP
#define BANK_HPP

#include <string>
#include <map>

class Bank {
private:
    std::string bankId;
    std::map<std::string, int> account;
public:
    // 생성자
    Bank();

    // 결제 메서드
    int pay(std::string cardNum, int cost);

    // 테스트용 메서드
    std::map<std::string, int> getAccount();
};

#endif // BANK_HPP