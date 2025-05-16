#ifndef AUTHCODEMANAGER_H
#define AUTHCODEMANAGER_H

#include <vector>
#include "AuthCode.hpp"

using namespace std;

class AuthCodeManager {
private:
    std::vector<AuthCode> AuthCodeList;

public:
    // 생성자
    AuthCodeManager();

    // 메서드
    AuthCode generateAuthCode() const;
    void saveAuthCode(int itemId, int itemNum, std::string code);
    bool isValidAuthCode(const std::string& code) const;
    void popAuthCode(int codeId);
};

#endif // AUTHCODEMANAGER_H