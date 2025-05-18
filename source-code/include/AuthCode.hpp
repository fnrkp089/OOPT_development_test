#ifndef AUTHCODE_H
#define AUTHCODE_H

#include <string>

using namespace std;

class AuthCode {
private:
    string code;
    int itemId;
    int itemNum;

public:
    // 생성자
    AuthCode(const string& code, int itemId, int itemNum);
  
    // Getter
    string getCode();
    int getItemId();
    int getItemNum();
};

#endif // AUTHCODE_H