// main은 그냥 알아서 컴파일하고 테스트파일만 cmake로 
#include "DVM.hpp"

using namespace std;

int main() {
     // DVM1: 아이디 1, 포트번호 5001, 좌표 (10,20)
    DVM dvm1("1", 10, 20, 5001);
    dvm1.run();

    // DVM2: 아이디 2, 포트번호 5002, 좌표 (4,5)
    //DVM dvm2("2", 5002, 4, 5);

    
    return 0;
}
