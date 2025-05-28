#include <P2PClient.hpp>
#include <MsgManager.hpp>

bool P2PClient::sendMessageToPeer(const std::string& ip, int port, const std::string& msg, std::string& response) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) return false;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        closesocket(sock);
        return false;
    }

    send(sock, msg.c_str(), (int)msg.length(), 0);
    char buffer[4096];
    int bytes = recv(sock, buffer, sizeof(buffer), 0);
    if (bytes > 0) response = std::string(buffer, bytes);

    closesocket(sock);
    return true;
}