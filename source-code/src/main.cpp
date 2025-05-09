#include "ExpressionEvaluator.hpp"
#include <iostream>

int main() {
    ExpressionEvaluator ev;
    std::string input;
    std::cout << "Enter expression: ";
    std::getline(std::cin, input);
    try {
        double result = ev.evaluate(input);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}
