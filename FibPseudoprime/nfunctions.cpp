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

int jacobi(int a) {
  long val = (new Mod(a, 5))->getA();
  if (val == 1 || val == 4) {
    return 1;
  } else if (val == 2 || val == 3) {
    return -1;
  } else
    return 0;
}

// uses matrix multiplication with repeated squares
long fib(int n) {
  // repeated squares
  long fibInit[2][2] = {{0, 1}, {1, 1}};
  long fibFinal[2][2] = {{1, 0}, {0, 1}};
  while (n > 0) {
    if (n % 2 == 1) {
      twoByTwo(fibFinal, fibInit);
    }
    twoByTwo(fibInit, fibInit);
    n = n / 2;
  }
  return fibFinal[0][1]; // + fibFinal[0][1];
}

void twoByTwo(long a[2][2], long b[2][2]) {
  long res[2][2] = {{}};
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        res[i][j] += a[i][k] * b[k][j];
      }
    }
  }

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      a[i][j] = res[i][j];
    }
  }
}
