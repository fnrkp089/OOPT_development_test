#include "AuthCode.hpp"

// 생성자 정의
AuthCode::AuthCode(const string& code, int itemId, int itemNum)
    : code(code), itemId(itemId), itemNum(itemNum) {}

// 인증코드 반환
string AuthCode::getCode(){
    return code;
}

// 음료수 번호 반환
int AuthCode::getItemId(){
    return itemId;
}

// 음료수 수량 반환
int AuthCode::getItemNum(){
    return itemNum;
}
