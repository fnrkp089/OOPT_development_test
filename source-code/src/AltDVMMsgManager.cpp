#include "AltDVMMsgManager.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

AltDVMMsgManager::AltDVMMsgManager(ItemManager* im, AuthCodeManager* am, AltDVMManager* adm, const string& selfId)
    : itemManager(im), authCodeManager(am), altDvmManager(adm), myId(selfId) {}

string AltDVMMsgManager::createRequestItemStockAndLocation() {
    int itemId = itemManager->getselectedItemId();
    int itemNum = itemManager->getselectedItemNum();
    ostringstream oss;
    oss << "{\n"
        << "  \"msg_type\": \"req_stock\",\n"
        << "  \"src_id\": \"" << myId << "\",\n"
        << "  \"dst_id\": \"0\",\n"
        << "  \"msg_content\": {\n"
        << "    \"item_code\": \"" << setw(2) << setfill('0') << itemId << "\",\n"
        << "    \"item_num\": \"" << setw(2) << setfill('0') << itemNum << "\"\n"
        << "  }\n}";
    return oss.str();
}

string AltDVMMsgManager::createPrepaymentAvailability(const string& dstId) {
    int itemId = itemManager->getselectedItemId();
    int itemNum = itemManager->getselectedItemNum();
    bool available = itemManager->isEnough();
    ostringstream oss;
    oss << "{\n"
        << "  \"msg_type\": \"resp_prepay\",\n"
        << "  \"src_id\": \"" << myId << "\",\n"
        << "  \"dst_id\": \"" << dstId << "\",\n"
        << "  \"msg_content\": {\n"
        << "    \"item_code\": \"" << setw(2) << setfill('0') << itemId << "\",\n"
        << "    \"item_num\": \"" << setw(2) << setfill('0') << itemNum << "\",\n"
        << "    \"availability\": \"" << (available ? "T" : "F") << "\"\n"
        << "  }\n}";
    return oss.str();
}

string AltDVMMsgManager::createRequestPrepayment(const string& dvmId, const string& authCode) {
    int itemId = itemManager->getselectedItemId();
    int itemNum = itemManager->getselectedItemNum();
    ostringstream oss;
    oss << "{\n"
        << "  \"msg_type\": \"req_prepay\",\n"
        << "  \"src_id\": \"" << myId << "\",\n"
        << "  \"dst_id\": \"" << dvmId << "\",\n"
        << "  \"msg_content\": {\n"
        << "    \"item_code\": \"" << setw(2) << setfill('0') << itemId << "\",\n"
        << "    \"item_num\": \"" << setw(2) << setfill('0') << itemNum << "\",\n"
        << "    \"cert_code\": \"" << authCode << "\"\n"
        << "  }\n}";
    return oss.str();
}

string AltDVMMsgManager::createItemStockAndLocation(const string& dstId, int coorX, int coorY) {
    int itemId = itemManager->getselectedItemId();
    int itemNum = itemManager->getselectedItemNum();
    ostringstream oss;
    oss << "{\n"
        << "  \"msg_type\": \"resp_stock\",\n"
        << "  \"src_id\": \"" << myId << "\",\n"
        << "  \"dst_id\": \"" << dstId << "\",\n"
        << "  \"msg_content\": {\n"
        << "    \"item_code\": \"" << setw(2) << setfill('0') << itemId << "\",\n"
        << "    \"item_num\": \"" << setw(2) << setfill('0') << itemNum << "\",\n"
        << "    \"coor_x\": \"" << coorX << "\",\n"
        << "    \"coor_y\": \"" << coorY << "\"\n"
        << "  }\n}";
    return oss.str();
}

void AltDVMMsgManager::receivePrepayResponse(const string& srcId, const string& availability, int coorX, int coorY) {
    altDvmManager->addDVM(srcId, coorX, coorY, availability);
}

void AltDVMMsgManager::requestItemStockAndLocation() {
    sendTo("0", createRequestItemStockAndLocation());
}

void AltDVMMsgManager::sendPrepaymentAvailability(const string& dstId) {
    sendTo(dstId, createPrepaymentAvailability(dstId));
}

void AltDVMMsgManager::requestPrepayment(const string& dvmId, const string& authCode) {
    sendTo(dvmId, createRequestPrepayment(dvmId, authCode));
}

void AltDVMMsgManager::sendItemStockAndLocation(const string& requesterId, int coorX, int coorY) {
    sendTo(requesterId, createItemStockAndLocation(requesterId, coorX, coorY));
}

void AltDVMMsgManager::sendTo(const string& dstId, const string& msg) {
    cout << "\n[Sending to " << dstId << "]\n" << msg << endl;
}
