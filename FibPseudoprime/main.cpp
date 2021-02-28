#include "nfunctions.hpp"
#include <iostream>

void printFactors(std::vector<std::pair<long, int>> factors) {
  std::cout << "[";
  for (std::pair<long, int> f : factors) {
    std::cout << "(" << f.first << ", " << f.second << "), ";
  }
  std::cout << "]";
}

int main() {
  long n = 5563 * 2 * 3 * 5 * 49 * 686989L;

  printFactors(factorize(n));

  return 0;
}
