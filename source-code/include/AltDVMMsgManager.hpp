#pragma once
#include "ItemManager.hpp"
#include "AuthCodeManager.hpp"
#include "AltDVMManager.hpp"
#include <string>

class AltDVMMsgManager {
private:
    ItemManager* itemManager;
    AuthCodeManager* authCodeManager;
    AltDVMManager* altDvmManager;
    std::string myId;

public:
    AltDVMMsgManager(ItemManager* im, AuthCodeManager* am, AltDVMManager* adm, const std::string& selfId);

    std::string createRequestItemStockAndLocation();
    std::string createPrepaymentAvailability(const std::string& dstId);
    std::string createRequestPrepayment(const std::string& dvmId, const std::string& authCode);
    std::string createItemStockAndLocation(const std::string& dstId, int coordX, int coordY);

    void requestItemStockAndLocation();
    void sendPrepaymentAvailability(const std::string& dstId);
    void requestPrepayment(const std::string& dvmId, const std::string& authCode);
    void sendItemStockAndLocation(const std::string& requesterId, int coordX, int coordY);

    void sendTo(const std::string& dstId, const std::string& msg);
    void receivePrepayResponse(const std::string& srcId, const std::string& availability, int coordX, int coordY);
};