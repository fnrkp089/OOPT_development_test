#include <P2PServer.hpp>
#include <MsgManager.hpp>
#include <iostream>

void P2PServer::listenLoop() {
    while (running) {
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket != INVALID_SOCKET) {
            std::thread(&P2PServer::handleClient, this, clientSocket).detach();
        }
    }
}

void P2PServer::handleClient(SOCKET clientSocket) {
    char buffer[4096];
    int bytes = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytes > 0) {
        std::string request(buffer, bytes);
        std::string response = processRequest(request);  // 너가 정의하는 처리
        send(clientSocket, response.c_str(), (int)response.length(), 0);
    }
    closesocket(clientSocket);
}