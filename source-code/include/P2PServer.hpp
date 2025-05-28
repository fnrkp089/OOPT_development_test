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
    
    using RequestHandler = std::function<std::string(const std::string&)>;
    RequestHandler handleRequest;

    void listenLoop();
    void handleClient(SOCKET clientSocket);
public:
    P2PServer(int port, RequestHandler handler);
    ~P2PServer();

    void start();
    void stop();
};