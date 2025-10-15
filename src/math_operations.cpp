#include "math_operations.h"
#include <stdexcept>

int MathOperations::add(int a, int b) { return a + b; }

int MathOperations::subtract(int a, int b) { return a - b; }

int MathOperations::multiply(int a, int b) { return a * b; }

double MathOperations::divide(int a, int b) {
  if (b == 0) {
    throw std::invalid_argument("Division by zero");
  }
  return static_cast<double>(a) / b;
}

bool MathOperations::isEven(int number) { return number % 2 == 0; }

int MathOperations::factorial(int n) {
  if (n < 0)
    throw std::invalid_argument("Negative number");
  if (n == 0 || n == 1)
    return 1;

  int result = 1;
  for (int i = 2; i <= n; ++i) {
    result *= i;
  }
  return result;
}
