cmake_minimum_required(VERSION 3.14)
project(DVM)

include(FetchContent)

# GoogleTest 다운로드 및 설정
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# 표준 및 디버깅 옵션
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0")

# dvm 라이브러리 정의 - 필요한 .cpp 전부 포함
add_library(dvm
    src/AuthCode.cpp
    src/AuthCodeManager.cpp
    src/Bank.cpp
    src/DVM.cpp
    src/Item.cpp
    src/ItemManager.cpp
    src/PaymentManager.cpp
    src/AltDVM.cpp
    src/AltDVMManager.cpp
    src/MsgManager.cpp
    src/P2PClient.cpp
    src/P2PServer.cpp
)

target_include_directories(dvm PUBLIC include)

# 실행 파일 (메인 프로그램)
add_executable(dvm_main src/main.cpp)
target_link_libraries(dvm_main PRIVATE dvm)

# 테스트 설정
enable_testing()

add_executable(testCode test/testCode.cpp)
target_link_libraries(testCode PRIVATE dvm gtest gtest_main)

add_test(NAME testCode COMMAND testCode)