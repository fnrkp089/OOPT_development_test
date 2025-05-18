// main은 그냥 알아서 컴파일하고 테스트파일만 cmake로 
#include "DVM.hpp"
#include "SocketClient.hpp"
#include <iostream>

using namespace std;

int main() {
    SocketClient client;

    // 서버 IP 및 포트 설정
    const string serverIP = "127.0.0.1";
    const int serverPort = 9000;

    if(!client.connectToServer(serverIP, serverPort)) {
        cerr << "서버에 연결할 수 없습니다." << endl;
        return 1;
    }
    cout << "서버에 연결되었습니다." << endl;

    // DVM 생성 (아이디, 좌표 설정)
    DVM dvm("1",2,3);

    client.closeConnection();
    cout << "서버와의 연결이 종료되었습니다." << endl;

    return 0;
}
