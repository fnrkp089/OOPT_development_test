#include "SocketClient.hpp"
#include <iostream>

using namespace std;

SocketClient::SocketClient(const string& ip, int port)
    : serverIp(ip), serverPort(port), clientSocket(INVALID_SOCKET) {
    WSAStartup(MAKEWORD(2, 2), &wsaData);
}

SocketClient::~SocketClient() {
    closeConnection();
    WSACleanup();
}

bool SocketClient::connectToServer() {
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cerr << "소켓 생성 실패\n";
        return false;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIp.c_str());

    if (connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cerr << "서버 연결 실패\n";
        closesocket(clientSocket);
        return false;
    }

    return true;
}

bool SocketClient::sendMessage(const string& msg) {
    int sendResult = send(clientSocket, msg.c_str(), static_cast<int>(msg.size()), 0);
    return sendResult != SOCKET_ERROR;
}

string SocketClient::receiveMessage() {
    char buffer[4096];
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesReceived > 0) {
        return string(buffer, bytesReceived);
    }
    return "";
}

void SocketClient::closeConnection() {
    if (clientSocket != INVALID_SOCKET) {
        closesocket(clientSocket);
        clientSocket = INVALID_SOCKET;
    }
}