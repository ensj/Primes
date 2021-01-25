#include "Mod.hpp"

Mod::Mod() { a = n = 0; }

Mod::Mod(long x, long y) {
  assert(y > 0);
  a = x;
  n = y;
  reduce();
}

void Mod::reduce() { a = ((a % n) + n) % n; }

long Mod::getA() { return a; }

long Mod::getN() { return n; }

bool Mod::isEmpty() { return a == 0 && n == 0; }

Mod Mod::operator+(const Mod &modObj) {
  Mod ans;

  if (n == modObj.n) {
    ans.n = n;
    ans.a = a + modObj.a;
    ans.reduce();
  }

  return ans;
}

Mod Mod::operator+(const int val) {
  Mod ans;
  ans.n = n;
  ans.a = a + val;
  ans.reduce();
  return ans;
}

Mod Mod::operator-(const Mod &modObj) {
  Mod ans;
  if (n == modObj.n) {
    ans.n = n;
    ans.a = a - modObj.a;
    ans.reduce();
  }
  return ans;
}

Mod Mod::operator-(const int val) {
  Mod ans;
  ans.n = n;
  ans.a = a - val;
  ans.reduce();
  return ans;
}

Mod Mod::operator*(const Mod &modObj) {
  Mod ans;
  if (n == modObj.n) {
    ans.n = n;
    ans.a = a * modObj.a;
    ans.reduce();
  }
  return ans;
}

Mod Mod::operator*(const int val) {
  Mod ans;
  ans.n = n;
  ans.a = val * a;
  ans.reduce();
  return ans;
}

Mod operator*(const int val, const Mod &modObj) {
  Mod ans(modObj.a, modObj.n);
  return ans * val;
}

// inverses
// Mod Mod::operator/(const Mod &a);

Mod Mod::operator^(int pow) {
  // repeated squares
  Mod temp(a, n);
  Mod ans;
  ans.a = 1;
  ans.n = n;
  while (pow > 0) {
    if (pow % 2 == 1) {
      ans.a = ans.a * temp.a;
      ans.reduce();
    }
    temp.a = (temp.a * temp.a) % temp.n;
    temp.reduce();
    pow = pow / 2;
  }
  return ans;
}

Mod Mod::operator%(const int m) {
  Mod ans;
  if (n % m == 0) {
    ans.n = m;
    ans.a = a;
    ans.reduce();
  }
  return ans;
}

bool Mod::operator==(const Mod &modObj) {
  if (n != modObj.n)
    return false;
  if (a == modObj.a) {
    return true;
  } else
    return false;
}

bool Mod::operator==(long val) {
  while (val < 0) {
    val = val + n;
  }
  val = val % n;

  if (val == a) {
    return true;
  } else
    return false;
}

std::string Mod::getString() const {
  return "Mod(" + std::to_string(a) + ", " + std::to_string(n) + ")";
}

std::ostream &operator<<(std::ostream &os, const Mod &modObj) {
  os << modObj.getString();
  return os;
}
