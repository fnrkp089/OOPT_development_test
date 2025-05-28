#pragma once
#include "ItemManager.hpp"
#include "AuthCodeManager.hpp"
#include "AltDVMManager.hpp"
#include "P2PClient.hpp"
#include <string>

class MsgManager {
private:
    ItemManager* itemManager;
    AuthCodeManager* authCodeManager;
    AltDVMManager* altDvmManager;
    P2PClient* p2pClient;
    std::string myId;

public:
    MsgManager(ItemManager* im, AuthCodeManager* am, AltDVMManager* adm, P2PClient* pc, const std::string& id);

    // 메시지 생성
    std::string createRequestItemStockAndLocation(const std::string& itemCode, int item_num);
    std::string createResponseItemStockAndLocation(const std::string& dstId, const std::string& itemCode, int itemNum, int coorX, int coorY);
    std::string createRequestPrepayment(const std::string& dstId, const std::string& itemCode, int itemNum, const std::string& certCode);
    std::string createResponsePrepayment(const std::string& dstId, const std::string& itemCode, int itemNum, const std::string& availability);

    // 메시지 송수신
    void sendTo(const std::string& dstId, const std::string& msg);  // 메시지 전송
    std::string receive(const std::string& rawMsg);                 // 메시지 수신 및 파싱

};