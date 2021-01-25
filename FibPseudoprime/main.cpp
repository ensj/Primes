#include "nfunctions.hpp"
#include <iostream>

int main() {
  long n = 5563 * 2 * 3 * 5 * 7;

  while (true) {
    long factor = ECFactor(n, 3000, 200);

    std::cout << "n: " << n << ", factor: " << factor << std::endl;

    if (factor == 1)
      break;

    n = n / factor;
  }
  return 0;
}
