#pragma once
#include <string>
#include <vector>

class ExpressionEvaluator {
public:
    double evaluate(const std::string& expr);

private:
    std::vector<std::string> tokenize(const std::string& expr);
    std::vector<std::string> toPostfix(const std::vector<std::string>& tokens);
    double computePostfix(const std::vector<std::string>& postfix);
    int precedence(const std::string& op);
    bool isOperator(const std::string& token);
};
