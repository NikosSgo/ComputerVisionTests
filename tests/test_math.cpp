#include "math_operations.h"
#include <gtest/gtest.h>

// Тесты для сложения
TEST(MathOperationsTest, Addition) {
  EXPECT_EQ(MathOperations::add(2, 3), 5);
  EXPECT_EQ(MathOperations::add(-1, 1), 0);
  EXPECT_EQ(MathOperations::add(0, 0), 0);
  EXPECT_EQ(MathOperations::add(-5, -3), -8);
}

// Тесты для вычитания
TEST(MathOperationsTest, Subtraction) {
  EXPECT_EQ(MathOperations::subtract(5, 3), 2);
  EXPECT_EQ(MathOperations::subtract(3, 5), -2);
  EXPECT_EQ(MathOperations::subtract(0, 0), 0);
  EXPECT_EQ(MathOperations::subtract(-5, -3), -2);
}

// Тесты для умножения
TEST(MathOperationsTest, Multiplication) {
  EXPECT_EQ(MathOperations::multiply(2, 3), 6);
  EXPECT_EQ(MathOperations::multiply(-2, 3), -6);
  EXPECT_EQ(MathOperations::multiply(2, -3), -6);
  EXPECT_EQ(MathOperations::multiply(-2, -3), 6);
  EXPECT_EQ(MathOperations::multiply(0, 5), 0);
}

// Тесты для деления
TEST(MathOperationsTest, Division) {
  EXPECT_DOUBLE_EQ(MathOperations::divide(6, 3), 2.0);
  EXPECT_DOUBLE_EQ(MathOperations::divide(5, 2), 2.5);
  EXPECT_DOUBLE_EQ(MathOperations::divide(0, 5), 0.0);
}

// Тест деления на ноль
TEST(MathOperationsTest, DivisionByZero) {
  EXPECT_THROW(MathOperations::divide(5, 0), std::invalid_argument);
}

// Тесты для проверки четности
TEST(MathOperationsTest, EvenCheck) {
  EXPECT_TRUE(MathOperations::isEven(4));
  EXPECT_TRUE(MathOperations::isEven(0));
  EXPECT_TRUE(MathOperations::isEven(-2));
  EXPECT_FALSE(MathOperations::isEven(5));
  EXPECT_FALSE(MathOperations::isEven(-3));
}

// Тесты для факториала
TEST(MathOperationsTest, Factorial) {
  EXPECT_EQ(MathOperations::factorial(0), 1);
  EXPECT_EQ(MathOperations::factorial(1), 1);
  EXPECT_EQ(MathOperations::factorial(5), 120);
  EXPECT_EQ(MathOperations::factorial(6), 720);
}

// Тест факториала отрицательного числа
TEST(MathOperationsTest, FactorialNegative) {
  EXPECT_THROW(MathOperations::factorial(-1), std::invalid_argument);
  EXPECT_THROW(MathOperations::factorial(-5), std::invalid_argument);
}

// Параметризованный тест для сложения
class AdditionTest
    : public ::testing::TestWithParam<std::tuple<int, int, int>> {};

TEST_P(AdditionTest, VariousInputs) {
  auto params = GetParam();
  int a = std::get<0>(params);
  int b = std::get<1>(params);
  int expected = std::get<2>(params);

  EXPECT_EQ(MathOperations::add(a, b), expected);
}

INSTANTIATE_TEST_SUITE_P(AdditionVariants, AdditionTest,
                         ::testing::Values(std::make_tuple(1, 1, 2),
                                           std::make_tuple(10, 20, 30),
                                           std::make_tuple(-5, 5, 0),
                                           std::make_tuple(100, -50, 50),
                                           std::make_tuple(0, 0, 0)));
