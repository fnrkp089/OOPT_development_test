#ifndef AUTHCODEMANAGER_H
#define AUTHCODEMANAGER_H

#include <vector>
#include "AuthCode.hpp"

using namespace std;

class AuthCodeManager {
private:
    vector<AuthCode> authCodeList;

public:
    // 생성자
    AuthCodeManager();

    // 메서드
    string generateCode(); // 무작위 문자열 코드 발급
    AuthCode makeAuthCode(const string& code, int itemId, int itemNum); // 전달용 인증코드 생성
    void saveAuthCode(const string& code, int itemId, int itemNum); // 전달받은 인증코드 저장
    bool isValidAuthCode(const string& code); // 해당 인증코드가 존재하는지 확인
    std::pair<int,int> popAuthCode(const string& code); // 사용된 인증 코드 삭제
    
    // 추가 메서드
};

#endif // AUTHCODEMANAGER_H