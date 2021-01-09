#ifndef MOD_H
#define MOD_H

#include <iostream>

struct Mod {
  int a, n; // a (mod n)
  Mod(int x = 0, int y = 1);

  void reduce();
};

std::ostream &operator<<(std::ostream &os, const Mod &a);

Mod operator+(const Mod &a, const Mod &b);
Mod operator+(const int &a, const Mod &b);
Mod operator+(const Mod &a, const int &b);

Mod operator-(const Mod &a, const Mod &b);
Mod operator-(const int &a, const Mod &b);
Mod operator-(const Mod &a, const int &b);

Mod operator*(const Mod &a, const Mod &b);
Mod operator*(const int &a, const Mod &b);
Mod operator*(const Mod &a, const int &b);

Mod operator/(const Mod &a, const int &b);

Mod operator^(Mod a, int b);

Mod operator%(const Mod &a, const int &b);

bool operator==(const Mod &a, const Mod &b);
bool operator==(const int &a, const Mod &b);
bool operator==(const Mod &a, const int &b);

#endif // MOD_H
