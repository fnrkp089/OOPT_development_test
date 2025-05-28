#include "MsgManager.hpp"
#include <json.hpp>
#include <iostream>
#include <cctype>

using json = nlohmann::json;

MsgManager::MsgManager(ItemManager* im, AuthCodeManager* am, AltDVMManager* adm, P2PClient* pc, const std::string& id)
    : itemManager(im), authCodeManager(am), altDvmManager(adm), p2pClient(pc), myId(id) {}

// 재고 확인 요청 메시지 생성
std::string MsgManager::createRequestItemStockAndLocation(const std::string& itemCode, int itemNum) {
    json j;
    j["msg_type"] = "req_stock";
    j["src_id"] = myId;
    j["dst_id"] = 0;
    j["msg_content"]["item_code"] = itemCode;
    j["msg_content"]["item_num"] = itemNum;
    return j.dump();
}

// 재고 확인 응답 메시지 생성
std::string MsgManager::createResponseItemStockAndLocation(const std::string& dstId, const std::string& itemCode, int itemNum, int coorX, int coorY) {
    json j;
    j["msg_type"] = "resp_stock";
    j["src_id"] = myId;
    j["dst_id"] = dstId;
    j["msg_content"]["item_code"] = itemCode;
    j["msg_content"]["item_num"] = itemNum;
    j["msg_content"]["coor_x"] = coorX;
    j["msg_content"]["coor_y"] = coorY;
    return j.dump();
}

// 선결제 요청 메시지 생성
std::string MsgManager::createRequestPrepayment(const std::string& dstId, const std::string& itemCode, int itemNum, const std::string& certCode) {
    json j;
    j["msg_type"] = "req_prepay";
    j["src_id"] = myId;
    j["dst_id"] = dstId;
    j["msg_content"]["item_code"] = itemCode;
    j["msg_content"]["item_num"] = itemNum;
    j["msg_content"]["cert_code"] = certCode;
    return j.dump();
}

// 선결제 가능 여부 응답 메시지 생성
std::string MsgManager::createResponsePrepayment(const std::string& dstId, const std::string& itemCode, int itemNum, const std::string& availability) {
    json j;
    j["msg_type"] = "resp_prepay";
    j["src_id"] = myId;
    j["dst_id"] = dstId;
    j["msg_content"]["item_code"] = itemCode;
    j["msg_content"]["item_num"] = itemNum;
    j["msg_content"]["availability"] = availability; // "T" 또는 "F"
    return j.dump();
}

// 메시지 전송
void MsgManager::sendTo(const std::string& dstId, const std::string& msg) {
    int basePort = 5000;
    int dvmNum = 0;
    try {
        if (!dstId.empty() && !std::isdigit(dstId.front())) {
            dvmNum = std::stoi(dstId.substr(1));
        } else {
            dvmNum = std::stoi(dstId);
        }
    } catch (const std::exception& e) {
        std::cerr << "[MsgManager] Invalid dstId: " << dstId << "\n";
        return;
    }

    int targetPort = basePort + dvmNum;
    std::string response;
    p2pClient->sendMessageToPeer("127.0.0.1", targetPort, msg, response);
}

// 메시지 수신 및 파싱
std::string MsgManager::receive(const std::string& rawMsg) {
    try {
        json j = json::parse(rawMsg);
        std::string type = j["msg_type"];

        // 재고 확인 요청 
        // dvm에서 좌표 값을 받아올 방법이 없음
        if (type == "req_stock") {
            std::string itemCode = j["msg_content"]["item_code"];
            std::string dstId = j["src_id"];
            int itemNum = itemManager->getStock(itemCode);
            return createResponseItemStockAndLocation(dstId, itemCode, itemNum, 0, 0);
        }
        // 재고 확인 응답 끝
        else if (type == "resp_stock") {
            std::string itemCode = j["msg_content"]["item_code"];
            int itemNum = j["msg_content"]["item_num"];
            int coorX = j["msg_content"]["coor_x"];
            int coorY = j["msg_content"]["coor_y"];
            std::string srcId = j["src_id"];
            if(itemManager->getSelectedItemNum() < itemNum)
                altDvmManager->addDVM(srcId,coorX,coorY,"T");
            else
                altDvmManager->addDVM(srcId,coorX,coorY,"F");

            return "STOCK_INFO_UPDATED";
        }
        // 선결제 요청 끝
        else if (type == "req_prepay") {
            std::string dstId = j["src_id"];
            std::string itemCode = j["msg_content"]["item_code"];
            int itemNum = j["msg_content"]["item_num"];
            std::string certCode = j["msg_content"]["cert_code"];
            std::string availability;

            if(itemManager->isEnough(stoi(itemCode))){
                itemManager->minusStock(stoi(itemCode), itemNum);
                authCodeManager->saveAuthCode(certCode,stoi(itemCode), itemNum);
                availability = "T";
            }
            else{
                availability = "F";
            }

            return createResponsePrepayment(dstId, itemCode, itemNum, availability);
        }
        // 선결제 응답
        else if (type == "resp_prepay") {
            std::string availability = j["msg_content"]["availability"];

            if(availability == "T") { // 해당 대안 자판기에 인증코드 저장이 완료된 경우
                // 선결제 성공
                return "PREPAYMENT_SUCCESS";
            } else {
                return "PREPAYMENT_FAILED";
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Error parsing message: " << e.what() << std::endl;
        return "{\"msg_type\":\"ERROR\"}";
    }

    return "{\"msg_type\":\"UNKNOWN\"}";
}