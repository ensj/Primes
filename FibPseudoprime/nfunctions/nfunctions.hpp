#ifndef NFUNCTIONS_H
#define NFUNCTIONS_H

#include "Mod.hpp"
#include <vector>

long gcd(long a, long b);
long gcd(Mod a);
long gcd(Mod a, long b);
long gcd(long a, Mod b);
long gcd(Mod a, Mod b);

long extendedGcd(long a, long b, long &x, long &y);

std::pair<Mod, long> invMod(long a, long m);
std::pair<Mod, long> invMod(Mod a);

int eulerphi(int a);

bool carmichael(int a);

int jacobi(long a);

long fib(int n);

void twoByTwo(long a[2][2], long b[2][2]);

std::vector<bool> baseTwo(int n);

std::vector<Mod> chooseEAndP(long n);

// long ECAdd(Mod a, Mod b, Mod &x1, Mod &y1, Mod x2, Mod y2);

// long ECDouble(Mod a, Mod b, Mod &x1, Mod &y1);

// long ECMultiply(Mod a, Mod b, Mod &x, Mod &y, int t);

// long findRFactorialPOnE(int r, Mod a, Mod b, Mod x, Mod y);

// long ECFactor(long n, int r, int tries);

std::vector<std::pair<long, int>> factorize(long n);

// forgot to make you do this one in the code review
void FibProduct(std::vector<size_t> one, std::vector<size_t> two);

#endif // NFUNCTIONS_H
