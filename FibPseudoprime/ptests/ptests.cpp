#include "ptests.hpp"

// pre: (a, b) = 1
// post: returns true if a is a probable prime base b, false otherwise
bool fermatTest(int a, int b) {
  if (gcd(a, b) == 1)
    return false;
  Mod n(b, a);
  n = n ^ (a - 1);
  if (n.getA() == 1)
    return true;
  return false;
}

bool strongFermatTest(int a, int b) {
  if (gcd(a, b) != 1)
    return false;

  int t = a - 1;
  int j = 0;
  while (t % 2 == 0 && t != 0) {
    j++;
    t /= 2;
  }
  Mod n(b, a);
  n = n ^ t;
  if (n.getA() == 1 || n.getA() == a - 1)
    return true;
  while (j > 0) {
    n = n ^ 2;
    if (n.getA() == a - 1)
      return true;
    j--;
  }
  return false;
}

// confirms if the nth fermat number is prime
// the nth fermat number is defined as (2 ^ 2 ^ n) + 1
bool pepinTest(int n) {
  int Fn = (1 << (1 << n)) + 1; // (2 ^ 2 ^ n) + 1

  Mod m(3, Fn);
  m = m ^ ((Fn - 1) / 2);

  if (m.getA() == Fn - 1)
    return true;
  return false;
}

bool fibTest(int n) { return true; }

bool millerRabin(long n, int k) {
  if (n <= 3)
    return true;
  if (n % 2 == 0)
    return false;

  int r = (int)log2(n - 1);
  int d = (n - 1) / pow(2, r);
  for (int i = 0; i < k; i++) {
    Mod x = Mod((rand() + 2) % (n - 2), n) ^ d;

    if (x == 1 || x == -1) {
      continue;
    }

    for (int j = 0; j < r - 1; j++) {
      x = x ^ 2;
      if (x == -1)
        break;

      return false;
    }
  }

  return true;
}