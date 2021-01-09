#include "Mod.hpp"

Mod::Mod(int x, int y) : a(x), n(y) {
  assert(y > 0);
  reduce();
}

void Mod::reduce() {
  while (a < 0)
    a = a + n;
  if (a > n) {
    a = a % n;
  }
}

std::ostream &operator<<(std::ostream &os, const Mod &a) {
  os << "Mod(" + std::to_string(a.a) + ", " + std::to_string(a.n) + ")";
  return os;
}

Mod operator+(const Mod &a, const Mod &b) {
  Mod ans;
  if (a.n == b.n) {
    ans.n = a.n;
    ans.a = a.a + b.a;
    ans.reduce();
  }
  return ans;
}

Mod operator+(const int &a, const Mod &b) {
  Mod ans;
  ans.n = b.n;
  ans.a = a + b.a;
  ans.reduce();
  return ans;
}

Mod operator+(const Mod &a, const int &b) { return b + a; }

Mod operator-(const Mod &a, const Mod &b) {
  Mod ans;
  if (a.n == b.n) {
    ans.n = a.n;
    ans.a = a.a - b.a;
    ans.reduce();
  }
  return ans;
}

Mod operator-(const int &a, const Mod &b) {
  Mod ans;
  ans.n = b.n;
  ans.a = a - b.a;
  ans.reduce();
  return ans;
}

Mod operator-(const Mod &a, const int &b) {
  Mod ans;
  ans.n = a.n;
  ans.a = a.a - b;
  ans.reduce();
  return ans;
}

Mod operator*(const Mod &a, const Mod &b) {
  Mod ans;
  if (a.n == b.n) {
    ans.n = a.n;
    ans.a = a.a * b.a;
    ans.reduce();
  }
  return ans;
}

Mod operator*(const int &a, const Mod &b) {
  Mod ans;
  ans.n = b.n;
  ans.a = a * b.a;
  ans.reduce();
  return ans;
}
Mod operator*(const Mod &a, const int &b) { return b * a; }

// inverses
Mod operator/(const Mod &a, const int &b);

Mod operator^(Mod a, int b) {
  // repeated squares
  Mod ans;
  ans.a = 1;
  ans.n = a.n;
  while (b > 0) {
    if (b % 2 == 1) {
      ans.a = ans.a * a.a;
      ans.reduce();
    }
    a.a = (a.a * a.a) % a.n;
    a.reduce();
    b = b / 2;
  }
  return ans;
}

Mod operator%(const Mod &a, const int &b) {
  Mod ans;
  if (a.n % b == 0) {
    ans.n = b;
    ans.a = a.a;
    ans.reduce();
  }
  return ans;
}

bool operator==(const Mod &a, const Mod &b) {
  if (a.n != b.n)
    return false;
  if (a.a == b.a) {
    return true;
  } else
    return false;
}