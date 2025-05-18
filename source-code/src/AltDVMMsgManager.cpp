#include "AltDVMMsgManager.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

AltDVMMsgManager::AltDVMMsgManager(ItemManager* im, AuthCodeManager* am, AltDVMManager* adm, const std::string& selfId)
    : itemManager(im), authCodeManager(am), altDvmManager(adm), myId(selfId) {}

std::string AltDVMMsgManager::createRequestItemStockAndLocation() {
    int itemId = itemManager->getselectedItemId();
    int itemNum = itemManager->getselectedItemNum();
    std::ostringstream oss;
    oss << "{\n"
        << "  \"msg_type\": \"req_stock\",\n"
        << "  \"src_id\": \"" << myId << "\",\n"
        << "  \"dst_id\": \"0\",\n"
        << "  \"msg_content\": {\n"
        << "    \"item_code\": \"" << std::setw(2) << std::setfill('0') << itemId << "\",\n"
        << "    \"item_num\": \"" << std::setw(2) << std::setfill('0') << itemNum << "\"\n"
        << "  }\n}";
    return oss.str();
}

std::string AltDVMMsgManager::createPrepaymentAvailability(const std::string& dstId) {
    int itemId = itemManager->getselectedItemId();
    int itemNum = itemManager->getselectedItemNum();
    bool available = itemManager->isEnough();
    std::ostringstream oss;
    oss << "{\n"
        << "  \"msg_type\": \"resp_prepay\",\n"
        << "  \"src_id\": \"" << myId << "\",\n"
        << "  \"dst_id\": \"" << dstId << "\",\n"
        << "  \"msg_content\": {\n"
        << "    \"item_code\": \"" << std::setw(2) << std::setfill('0') << itemId << "\",\n"
        << "    \"item_num\": \"" << std::setw(2) << std::setfill('0') << itemNum << "\",\n"
        << "    \"availability\": \"" << (available ? "T" : "F") << "\"\n"
        << "  }\n}";
    return oss.str();
}

std::string AltDVMMsgManager::createRequestPrepayment(const std::string& dvmId, const std::string& authCode) {
    int itemId = itemManager->getselectedItemId();
    int itemNum = itemManager->getselectedItemNum();
    std::ostringstream oss;
    oss << "{\n"
        << "  \"msg_type\": \"req_prepay\",\n"
        << "  \"src_id\": \"" << myId << "\",\n"
        << "  \"dst_id\": \"" << dvmId << "\",\n"
        << "  \"msg_content\": {\n"
        << "    \"item_code\": \"" << std::setw(2) << std::setfill('0') << itemId << "\",\n"
        << "    \"item_num\": \"" << std::setw(2) << std::setfill('0') << itemNum << "\",\n"
        << "    \"cert_code\": \"" << authCode << "\"\n"
        << "  }\n}";
    return oss.str();
}

std::string AltDVMMsgManager::createItemStockAndLocation(const std::string& dstId, int coordX, int coordY) {
    int itemId = itemManager->getselectedItemId();
    int itemNum = itemManager->getselectedItemNum();
    std::ostringstream oss;
    oss << "{\n"
        << "  \"msg_type\": \"resp_stock\",\n"
        << "  \"src_id\": \"" << myId << "\",\n"
        << "  \"dst_id\": \"" << dstId << "\",\n"
        << "  \"msg_content\": {\n"
        << "    \"item_code\": \"" << std::setw(2) << std::setfill('0') << itemId << "\",\n"
        << "    \"item_num\": \"" << std::setw(2) << std::setfill('0') << itemNum << "\",\n"
        << "    \"coor_x\": \"" << coordX << "\",\n"
        << "    \"coor_y\": \"" << coordY << "\"\n"
        << "  }\n}";
    return oss.str();
}

void AltDVMMsgManager::receivePrepayResponse(const std::string& srcId, const std::string& availability, int coordX, int coordY) {
    altDvmManager->addDVM(srcId, coordX, coordY, availability);
}

void AltDVMMsgManager::requestItemStockAndLocation() {
    sendTo("0", createRequestItemStockAndLocation());
}

void AltDVMMsgManager::sendPrepaymentAvailability(const std::string& dstId) {
    sendTo(dstId, createPrepaymentAvailability(dstId));
}

void AltDVMMsgManager::requestPrepayment(const std::string& dvmId, const std::string& authCode) {
    sendTo(dvmId, createRequestPrepayment(dvmId, authCode));
}

void AltDVMMsgManager::sendItemStockAndLocation(const std::string& requesterId, int coordX, int coordY) {
    sendTo(requesterId, createItemStockAndLocation(requesterId, coordX, coordY));
}

void AltDVMMsgManager::sendTo(const std::string& dstId, const std::string& msg) {
    std::cout << "\n[Sending to " << dstId << "]\n" << msg << std::endl;
}
