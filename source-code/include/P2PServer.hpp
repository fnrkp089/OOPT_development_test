#pragma once
#include <winsock2.h>
#include <thread>
#include <atomic>
#include <functional>
#include <string>

class P2PServer {
private:
    SOCKET listenSocket;
    int port;
    std::atomic<bool> running;
    std::thread serverThread;
    RequestHandler handleRequest;

    void listenLoop();
    void handleClient(SOCKET clientSocket);
public:
    using RequestHandler = std::function<std::string(const std::string&)>;

    P2PServer(int port, RequestHandler handler);
    ~P2PServer();

    void start();
    void stop();
};