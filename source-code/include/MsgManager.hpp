#pragma once
#include "ItemManager.hpp"
#include "AuthCodeManager.hpp"
#include "AltDVMManager.hpp"
#include <string>

class MsgManager {
private:
    ItemManager itemManager;
    AuthCodeManager authCodeManager;
    AltDVMManager altDvmManager;
    std::string myId;

public:
    MsgManager(ItemManager im, AuthCodeManager am, AltDVMManager adm, const std::string& selfId);

    std::string createRequestItemStockAndLocation();
    std::string createPrepaymentAvailability(const std::string& dstId);
    std::string createRequestPrepayment(const std::string& dvmId, AuthCode authCode);
    std::string createItemStockAndLocation(const std::string& dstId, int coorX, int coorY);

    void requestItemStockAndLocation();
    void sendPrepaymentAvailability(const std::string& dstId);
    void requestPrepayment(const std::string& dvmId, AuthCode authCode);
    void sendItemStockAndLocation(const std::string& requesterId, int coorX, int coorY);

    void sendTo(const std::string& dstId, const std::string& msg);
    void receivePrepayResponse(const std::string& srcId, const std::string& availability, int coorX, int coorY);
};