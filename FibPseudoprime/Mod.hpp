#ifndef MOD_H
#define MOD_H

#include <iostream>

class Mod {
public:
  Mod();
  Mod(long x, long y);

  long getA();
  long getN();

  Mod operator+(const Mod &modObj);
  Mod operator+(const int val);
  friend Mod operator+(const int val, const Mod &modObj);

  Mod operator-(const Mod &modObj);
  Mod operator-(const int val);
  friend Mod operator-(const int val, const Mod &modObj);

  Mod operator*(const Mod &modObj);
  Mod operator*(const int val);
  friend Mod operator*(const int val, const Mod &modObj);

  Mod operator/(const Mod &modObj);

  Mod operator^(int pow);

  Mod operator%(const int m);

  bool operator==(const Mod &modObj);
  bool operator==(long val);

  std::string getString() const;
  friend std::ostream &operator<<(std::ostream &os, const Mod &modObj);

private:
  long a, n;
  void reduce();
};

#endif // MOD_H
