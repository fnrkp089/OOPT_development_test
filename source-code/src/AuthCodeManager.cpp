#include "AuthCodeManager.hpp"
#include <iostream>

// 생성자
AuthCodeManager::AuthCodeManager()
    : AuthCodeList() {
    // 빈 AuthCode 리스트 생성
}

void AuthCodeManager::saveAuthCode(int codeId, std::string& code, int itemId, int itemNum) const {
    AuthCode authCode(codeId, code, itemId, itemNum);
    AuthCodeList.push_back(authCode);
}

// 해당 인증코드가 존재하는지 확인
bool AuthCodeManager::isValidAuthCode(const std::string& code) const {
    for (const auto& authCode : AuthCodeList) {
        if (authCode.getCode() == code) {
            return true;
        }
    }
    return false;
}

// 사용된 인증 코드 삭제
void AuthCodeManager::popAuthCode(int codeId) {
    for (auto it = AuthCodeList.begin(); it != AuthCodeList.end(); ++it) {
        if (it->getCodeId() == codeId) {
            AuthCodeList.erase(it);
            break;
        }
    }
}
