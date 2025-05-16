#include "AuthCode.hpp"
#include <iostream>

// 생성자 정의
AuthCode::AuthCode(int codeId, const std::string& code, int itemId, int itemNum)
    : codeId(codeId), code(code), itemId(itemId), itemNum(itemNum) {}

// 코드 아이디 반환
int AuthCode::getCodeId() const {
    return codeId;
}

// 재고 반환
std::string getCode() const {
    return code;
}
