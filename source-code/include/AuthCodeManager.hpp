#ifndef AUTHCODEMANAGER_H
#define AUTHCODEMANAGER_H

#include <vector>
#include "AuthCode.hpp"

using namespace std;

class AuthCodeManager {
private:
    std::vector<AuthCode> authCodeList;

public:
    // 생성자
    AuthCodeManager();

    // 메서드
    AuthCode generateAuthCode() const;
    void saveAuthCode(int codeId, const std::string& code, int itemId, int itemNum);
    bool isValidAuthCode(const std::string& code);
    void popAuthCode(int codeId);
};

#endif // AUTHCODEMANAGER_H