#pragma once
#include <string>

class P2PClient {
public:
    P2PClient();
    ~P2PClient();

    bool sendMessageToPeer(const std::string& ip, int port, const std::string& msg, std::string& response);
};