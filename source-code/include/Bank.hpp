#ifndef BANK_HPP
#define BANK_HPP

#include <string>
#include <map>

using namespace std;

class Bank {
private:
    string bankId;
    map<string, int> account;
public:
    // 생성자
    Bank();

    // 결제 메서드
    int pay(string cardNum, int cost);
};

#endif // BANK_HPP