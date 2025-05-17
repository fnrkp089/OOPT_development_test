#include "AuthCode.hpp"

// 생성자 정의
AuthCode::AuthCode(const std::string& code, int itemId, int itemNum)
    : code(code), itemId(itemId), itemNum(itemNum) {}

// 재고 반환
std::string AuthCode::getCode(){
    return code;
}
