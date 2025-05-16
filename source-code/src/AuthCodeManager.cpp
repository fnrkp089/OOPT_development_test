#include "AuthCodeManager.hpp"
#include <iostream>

// 생성자
AuthCodeManager::AuthCodeManager()
    : authCodeList() {
    // 빈 AuthCode 리스트 생성
}

void AuthCodeManager::saveAuthCode(int codeId, const std::string& code, int itemId, int itemNum) {
    authCodeList.emplace_back(codeId, code, itemId, itemNum);
}

// 해당 인증코드가 존재하는지 확인
bool AuthCodeManager::isValidAuthCode(const std::string& code) {
    for (int iter = 0; iter<authCodeList.size(); iter++) {
        if (authCodeList[iter].getCode() == code) {
            return true;
        }
    }
    return false;
}

// 사용된 인증 코드 삭제
void AuthCodeManager::popAuthCode(int codeId) {
    for (auto it = authCodeList.begin(); it != authCodeList.end(); ++it) {
        if (it->getCodeId() == codeId) {
            authCodeList.erase(it);
            break;
        }
    }
}
