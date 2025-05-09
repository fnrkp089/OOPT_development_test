cmake_minimum_required(VERSION 3.14)
project(ExpressionEvaluator)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0")

# include 디렉토리 포함
include_directories(include)

# 수식 계산기 라이브러리
add_library(evaluator src/ExpressionEvaluator.cpp)

# 실행 파일 (main)
add_executable(expr_main src/main.cpp)
target_link_libraries(expr_main evaluator)

# 테스트 설정
enable_testing()
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_evaluator test/test_evaluator.cpp)
target_link_libraries(test_evaluator evaluator gtest gtest_main)

add_test(NAME EvaluatorTests COMMAND test_evaluator)
