#include "nfunctions.hpp"
#include <iostream>

std::string vectToString(std::vector<Mod> v) {
  std::string res = "{ ";

  for (size_t i = 0; i < v.size(); i++) {
    res += v[i].getString() + ", ";
  }
  res += "}";

  return res;
}

int main() {
  // long n = 2 * 7 * 7; // 5563 * 2 * 3 * 5 * 7;

  // std::cout << vectToString(chooseEAndP(n)) << std::endl;
  // std::cout << vectToString(chooseEAndP(n)) << std::endl;
  // std::cout << vectToString(chooseEAndP(n)) << std::endl;

  for (long n = 1; n < 100000; n++) {
    std::cout << "factoring: " << n << std::endl;

    long factorNum = n;

    while (true) {
      long factor = ECFactor(factorNum, 3000, 500);

      std::cout << "  n: " << factorNum << ", factor: " << factor << std::endl;

      if (factor == 1)
        break;

      factorNum = factorNum / factor;
    }
  }
  return 0;
}
