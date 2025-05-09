#include "ExpressionEvaluator.hpp"
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <cmath>

std::vector<std::string> ExpressionEvaluator::tokenize(const std::string& expr) {
    std::vector<std::string> tokens;
    std::stringstream ss;
    for (char ch : expr) {
        if (isspace(ch)) continue;
        if (isdigit(ch) || ch == '.') {
            ss << ch;
        } else {
            if (!ss.str().empty()) {
                tokens.push_back(ss.str());
                ss.str("");
            }
            tokens.push_back(std::string(1, ch));
        }
    }
    if (!ss.str().empty()) {
        tokens.push_back(ss.str());
    }
    return tokens;
}

int ExpressionEvaluator::precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}

bool ExpressionEvaluator::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

std::vector<std::string> ExpressionEvaluator::toPostfix(const std::vector<std::string>& tokens) {
    std::vector<std::string> output;
    std::stack<std::string> ops;
    for (const std::string& token : tokens) {
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
            output.push_back(token);
        } else if (token == "(") {
            ops.push(token);
        } else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                output.push_back(ops.top());
                ops.pop();
            }
            if (ops.empty()) throw std::invalid_argument("Mismatched parentheses");
            ops.pop();
        } else if (isOperator(token)) {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        } else {
            throw std::invalid_argument("Invalid token: " + token);
        }
    }
    while (!ops.empty()) {
        if (ops.top() == "(") throw std::invalid_argument("Mismatched parentheses");
        output.push_back(ops.top());
        ops.pop();
    }
    return output;
}

double ExpressionEvaluator::computePostfix(const std::vector<std::string>& postfix) {
    std::stack<double> s;
    for (const std::string& token : postfix) {
        if (isOperator(token)) {
            if (s.size() < 2) throw std::invalid_argument("Invalid expression");
            double b = s.top(); s.pop();
            double a = s.top(); s.pop();
            if (token == "+") s.push(a + b);
            else if (token == "-") s.push(a - b);
            else if (token == "*") s.push(a * b);
            else if (token == "/") {
                if (b == 0) throw std::invalid_argument("Division by zero");
                s.push(a / b);
            }
        } else {
            s.push(std::stod(token));
        }
    }
    if (s.size() != 1) throw std::invalid_argument("Invalid postfix evaluation");
    return s.top();
}

double ExpressionEvaluator::evaluate(const std::string& expr) {
    return computePostfix(toPostfix(tokenize(expr)));
}
