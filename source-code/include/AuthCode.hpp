#ifndef AUTHCODE_H
#define AUTHCODE_H

#include <string>

class AuthCode {
private:
    std::string code;
    int itemId;
    int itemNum;

public:
    // 생성자
    AuthCode(const std::string& code, int itemId, int itemNum);
  
    // Getter
    std::string getCode() const;
    int getItemId();
    int getItemNum();
};

#endif // AUTHCODE_H