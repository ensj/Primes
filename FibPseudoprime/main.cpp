#include "Mod.hpp"
#include "nfunctions.hpp"
#include "ptests.hpp"
#include <iostream>

using namespace std;

int main() {
  cout << "1st prime Fermat number: 3" << endl;
  int count = 2;
  for (int i = 1; i < 10; i++) {
    if (pepinTest(i)) {

      if (count % 10 == 1) {
        cout << count << "st prime Fermat number: ";
      } else if (count % 10 == 2) {
        cout << count << "nd prime Fermat number: ";
      } else if (count % 10 == 3) {
        cout << count << "rd prime Fermat number: ";
      } else {
        cout << count << "th prime Fermat number: ";
      }

      cout << ((1 << (1 << i)) + 1) << endl;
      count++;
    }
  }
  return 0;
}
