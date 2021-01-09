#include "nfunctions.hpp"

int gcd(int a, int b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int gcd(Mod a, int b);
int gcd(int a, Mod b);
int gcd(Mod a, Mod b);

int extendedGcd(int a, int b, int &x, int &y);
