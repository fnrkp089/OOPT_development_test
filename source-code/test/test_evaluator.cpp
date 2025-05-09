#include "ExpressionEvaluator.hpp"
#include <gtest/gtest.h>

TEST(ExpressionEvaluatorTest, BasicAddition) {
    ExpressionEvaluator ev;
    EXPECT_DOUBLE_EQ(ev.evaluate("2 + 3"), 5.0);
}

TEST(ExpressionEvaluatorTest, Parentheses) {
    ExpressionEvaluator ev;
    EXPECT_DOUBLE_EQ(ev.evaluate("2 * (3 + 4)"), 14.0);
}

TEST(ExpressionEvaluatorTest, OperatorPrecedence) {
    ExpressionEvaluator ev;
    EXPECT_DOUBLE_EQ(ev.evaluate("2 + 3 * 4"), 14.0);
}

TEST(ExpressionEvaluatorTest, InvalidExpression) {
    ExpressionEvaluator ev;
    EXPECT_THROW(ev.evaluate("3 + * 4"), std::invalid_argument);
}
