#include "MsgManager.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

MsgManager::MsgManager(ItemManager im, AuthCodeManager am, AltDVMManager adm, const string& selfId)
    : itemManager(im), authCodeManager(am), altDvmManager(adm), myId(selfId) {}

// item 재고와 자판기 위치를 요청하는 메세지 생성
string MsgManager::createRequestItemStockAndLocation() {
    int itemId = itemManager.getselectedItemId();
    int itemNum = itemManager.getselectedItemNum();
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

// 선결제 가능 여부 응답 메세지 생성
string MsgManager::createPrepaymentAvailability(const string& dstId) {
    int itemId = itemManager.getselectedItemId();
    int itemNum = itemManager.getselectedItemNum();
    bool available = itemManager.isEnough();
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

// 선결제 가능 여부 요청 메세지 생성
string MsgManager::createRequestPrepayment(const string& dvmId, AuthCode authCode) {
    int itemId = authCode.getItemId();
    int itemNum = authCode.getItemNum();
    string code = authCode.getCode();
    ostringstream oss;
    oss << "{\n"
        << "  \"msg_type\": \"req_prepay\",\n"
        << "  \"src_id\": \"" << myId << "\",\n"
        << "  \"dst_id\": \"" << dvmId << "\",\n"
        << "  \"msg_content\": {\n"
        << "    \"item_code\": \"" << setw(2) << setfill('0') << itemId << "\",\n"
        << "    \"item_num\": \"" << setw(2) << setfill('0') << itemNum << "\",\n"
        << "    \"cert_code\": \"" << code << "\"\n"
        << "  }\n}";
    return oss.str();
}

// item 재고와 자판기 위치를 응답하는 메세지 생성
string MsgManager::createItemStockAndLocation(const string& dstId, int coorX, int coorY) {
    int itemId = itemManager.getselectedItemId();
    int itemNum = itemManager.getselectedItemNum();
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

void MsgManager::receivePrepayResponse(const string& srcId, const string& availability, int coorX, int coorY) {
    altDvmManager.addDVM(srcId, coorX, coorY, availability);
}

// item 재고와 자판기 위치를 요청하는 메세지
void MsgManager::requestItemStockAndLocation() {
    sendTo("0", createRequestItemStockAndLocation());
}

// 선결제 가능 여부 응답 메세지
void MsgManager::sendPrepaymentAvailability(const string& dstId) {
    sendTo(dstId, createPrepaymentAvailability(dstId));
}

// 선결제 가능 여부 요청 메세지
void MsgManager::requestPrepayment(const string& dvmId, AuthCode authCode) {
    sendTo(dvmId, createRequestPrepayment(dvmId, authCode));
}

// item 재고와 자판기 위치를 응답하는 메세지
void MsgManager::sendItemStockAndLocation(const string& requesterId, int coorX, int coorY) {
    string msg = createItemStockAndLocation(requesterId, coorX, coorY);
    sendTo(requesterId, msg);
}

void MsgManager::sendTo(const std::string& dstId, const std::string& msg) {
    std::string ip = altDvmManager.getIp(dstId);   // AltDVMManager에서 DVM의 IP를 받아온다고 가정
    int port = altDvmManager.getPort(dstId);       // 포트도 마찬가지로

    SocketClient client(ip, port);
    if (client.connectToServer()) {
        if (!client.sendMessage(msg)) {
            std::cerr << "[ERROR] 메세지 전송 실패 to " << dstId << endl;
        } else {
            std::cout << "[INFO] 메세지 전송 성공 to " << dstId << endl;
        }
        client.closeConnection();
    } else {
        std::cerr << "[ERROR] " << dstId << " 연결 실패" << endl;
    }
}
