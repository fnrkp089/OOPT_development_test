// #ifndef SOCKET_CLIENT_HPP
// #define SOCKET_CLIENT_HPP

// #include <string>
// #include <winsock2.h>

// class SocketClient {
// private:
//     WSADATA wsaData;
//     SOCKET clientSocket;
//     sockaddr_in serverAddr;
//     std::string serverIp;
//     int serverPort;

// public:
//     SocketClient(const std::string& ip, int port);
//     ~SocketClient();

//     bool connectToServer();
//     bool sendMessage(const std::string& msg);
//     std::string receiveMessage();
//     void closeConnection();
// };

// #endif // SOCKET_CLIENT_HPP