#include "Bank.hpp"
#include <iostream>

using namespace std;

Bank::Bank() 
: bankId("신한은행"){
    account.insert(pair<string, int>("12345", 10000)); // test input
}

// 결제 처리 메서드
// 1: 성공, 2: 카드 정보 안 맞음, 3: 계좌에 돈이 부족함, -1: 예외상황 발생
// 예외 상황이 있나?
int Bank::pay(string cardNum, int cost) {
    for(auto iter : account){
        if(iter.first.compare(cardNum) == 0){
            if(iter.second >= cost){
                return 1;
            }
            else return 3;
        }
    }
    return 2;
}