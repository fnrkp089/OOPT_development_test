// main은 그냥 알아서 컴파일하고 테스트파일만 cmake로 
// #include "ExpressionEvaluator.hpp"
#include "DVM.hpp"
#include <iostream>

int main() {
    // ExpressionEvaluator ev;
    // std::string input;
    // std::cout << "Enter expression: ";
    // std::getline(std::cin, input);
    // try {
    //     double result = ev.evaluate(input);
    //     std::cout << "Result: " << result << std::endl;
    // } catch (const std::exception& ex) {
    //     std::cerr << "Error: " << ex.what() << std::endl;
    // }
    DVM dvm("1",2,3);

    return 0;
}
