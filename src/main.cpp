#include "math_operations.h"
#include <iostream>

int main() {
  std::cout << "=== Math Operations Demo ===" << std::endl;

  std::cout << "5 + 3 = " << MathOperations::add(5, 3) << std::endl;
  std::cout << "5 - 3 = " << MathOperations::subtract(5, 3) << std::endl;
  std::cout << "5 * 3 = " << MathOperations::multiply(5, 3) << std::endl;
  std::cout << "6 / 3 = " << MathOperations::divide(6, 3) << std::endl;

  std::cout << "Is 4 even? " << (MathOperations::isEven(4) ? "Yes" : "No")
            << std::endl;
  std::cout << "Factorial of 5 = " << MathOperations::factorial(5) << std::endl;

  return 0;
}
