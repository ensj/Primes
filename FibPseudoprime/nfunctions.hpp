#ifndef NFUNCTIONS_H
#define NFUNCTIONS_H

#include "Mod.hpp"

int gcd(int a, int b);
int gcd(Mod a, int b);
int gcd(int a, Mod b);
int gcd(Mod a, Mod b);

int extendedGcd(int a, int b, int &x, int &y);

int eulerphi(int a);

bool carmichael(int a);

int jacobi(int a);

long fib(int n);

void twoByTwo(long a[2][2], long b[2][2]);

#endif // NFUNCTIONS_H
