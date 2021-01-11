#include "Mod.hpp"
#include "nfunctions.hpp"
#include "ptests.hpp"
#include <iostream>

int main() {
  for (int i = 0; i < 10; i++) {
    std::cout << i << ": " << fib(i) << std::endl;
  }
  //    std::cout << "1st prime Fermat number: 3" << std::endl;
  //    int count = 2;
  //    for (int i = 1; i < 10; i++) {
  //        if (pepinTest(i)) {
  //            if (count % 10 == 1) {
  //                std::cout << count << "st prime Fermat number: ";
  //            } else if (count % 10 == 2) {
  //                std::cout << count << "nd prime Fermat number: ";
  //            } else if (count % 10 == 3) {
  //                std::cout << count << "rd prime Fermat number: ";
  //            } else {
  //                std::cout << count << "th prime Fermat number: ";
  //            }
  //
  //            long a = 1;
  //            std::cout << ((a << (1 << i)) + 1) << std::endl;
  //            count++;
  //        }
  //    }
  return 0;
}
