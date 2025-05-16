#ifndef AUTHCODE_H
#define AUTHCODE_H

#include <string>

class AuthCode {
private:
    int codeId;
    std::string code;
    int itemId;
    int itemNum;

public:
    // 생성자
    AuthCode(int codeId, const std::string& code, int itemId, int itemNum);

    // Getter
    int getCodeId() const;
    std::string getCode();
};

#endif // AUTHCODE_H