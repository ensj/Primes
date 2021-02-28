#include "nfunctions.hpp"
#include "ptests.hpp"
#include "smallprimes.hpp"
#include <cmath>

long gcd(long a, long b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

long gcd(Mod a) { return gcd(a.getA(), a.getN()); }

long gcd(Mod a, long b) { return gcd(a.getA(), b); }
long gcd(long a, Mod b) { return gcd(a, b.getA()); }
long gcd(Mod a, Mod b) { return gcd(a.getA(), b.getA()); }

long extendedGcd(long a, long b, long &x, long &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  long x1, y1;
  long d = extendedGcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}

// A function that takes as input b and c and returns gcd(b,c) and c^{-1} mod b
// After output, may need an immediate: if(gcd<>1, ... as that means you have
// succeeded in finding a factor and want to pull yourself out of the loop of
// trying different elliptic curves.
std::pair<Mod, long> invMod(long a, long m) {
  long x, y;
  long g = extendedGcd(a, m, x, y);
  if (g != 1) {
    return {Mod(), g};
  } else {
    return {Mod(x, m), g};
  }
}

std::pair<Mod, long> invMod(Mod modObj) {
  long a = modObj.getA();
  long m = modObj.getN();

  long x, y;
  long g = extendedGcd(a, m, x, y);
  if (g != 1) {
    return {Mod(), g};
  } else {
    return {Mod(x, m), g};
  }
}

// returns (n/5)
int jacobi(long a) {
  long val = Mod(a, 5).getA();
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
  return fibFinal[0][1];
}

// A function that performs 2x2 matrix multiplication
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

// A function that turns a positive integer t into its base 2 representation
std::vector<bool> baseTwo(int n) {
  std::vector<bool> res;
  while (n > 0) {
    res.push_back(n % 2);
    n = n / 2;
  }
  std::reverse(res.begin(), res.end());

  return res;
}

// A function that takes n and outputs A, B, xx, yy that give a random elliptic
// curve E and a random point P on E(Z/nZ).
std::vector<Mod> chooseEAndP(long n) {
  // creating rand for big int is a bit difficult.
  // For now we use std::random.
  Mod x(rand(), n);
  Mod y(rand(), n);
  Mod a(rand(), n);

  Mod b = (y ^ 2) - (x ^ 3) - (a * x);

  return std::vector<Mod>{x, y, a, b};
}

// A function that adds (x1, y1) + (x2, y2) on y^2=x^3+Ax+B mod n.
// Assumes x1 != x2. So will need "if x1<>x2 ..." statement before it.
// If x1 == x2, then abort this elliptic curve and point and start with a new
// one.
long ECAdd(Mod a, Mod b, Mod &x1, Mod &y1, Mod x2,
           Mod y2) { // return gcd instead
  std::pair<Mod, long> invPair = invMod(x2 - x1);
  Mod xxinv = invPair.first;

  if (invPair.second != 1)
    return invPair.second;

  Mod slope = (y2 - y1) * xxinv;
  Mod nu = (y1 * x2 - y2 * x1) * xxinv;
  x1 = (slope ^ 2) - x1 - x2;
  y1 = -1 * slope * x1 - nu;

  return invPair.second;
}

// A function that doubles the point (x1, y1) on y^2=x^3+Ax+B mod n. Assumes
// y1<>0. So will need "if y1<>0 ..." statement before it. if y1 == 0, then
// abort this elliptic curve and point and start with a new one.
long ECDouble(Mod a, Mod b, Mod &x1, Mod &y1) { // return gcd instead
  std::pair<Mod, long> invPair = invMod(2 * y1);
  Mod yyinv = invPair.first;

  if (invPair.second != 1)
    return invPair.second;

  Mod slope = (3 * (x1 ^ 2) + a) * yyinv;
  Mod nu = (-1 * (x1 ^ 3) + a * x1 + 2 * b) * yyinv;
  x1 = (slope ^ 2) - 2 * x1;
  y1 = -1 * slope * x1 - nu;

  return invPair.second;
}

// ECMultiply(A,B,xx,yy,t): A function that multiplies the point (xx,yy) on
// y^2=x^3+Ax+B mod n by t on the elliptic curve implementing repeated doubling.
// Note the double of the point (xx,0) is the 0-point. If you are supposed to
// get that, then I don't think this particular elliptic curve will help you
// find a factor of n. Hence the: if(PointToBeDoubled[1]<>0 Note the sum of the
// points (xx,yy) and (xx,-yy) is the 0-point. This will be rare and I don't
// want to deal with it. Hence the: if(PartialSum[1]<>PointToBeDoubled[1],
long ECMultiply(Mod a, Mod b, Mod &x, Mod &y, int t) {
  std::vector<bool> bits = baseTwo(t);
  size_t numbits = bits.size();

  std::vector<Mod> dpoint{x, y};
  std::vector<Mod> zpoint{Mod(), Mod()};

  if (bits[numbits - 1] == true)
    zpoint = {x, y};

  long gcd = 1;
  for (size_t i = numbits; i > 0; i -= 2) {
    if (dpoint[1].getA() != 0) {
      gcd = ECDouble(a, b, dpoint[0], dpoint[1]);
      if (gcd != 1)
        return gcd;
    } else
      break;

    if (bits[i]) {
      if (zpoint[0].isEmpty() && zpoint[1].isEmpty()) {
        zpoint = dpoint;
      } else if (dpoint[1] == zpoint[1]) {
        gcd = ECAdd(a, b, zpoint[0], zpoint[1], dpoint[0], dpoint[1]);
        if (gcd != 1)
          return gcd;
      } else
        break;
    }
  }

  x = zpoint[0];
  y = zpoint[1];

  return 1;
}

// A function that finds r! * P on E mod n where P = (xx,yy) and E given by y^2
// = x^3 + Ax + B mod n.
long findRFactorialPOnE(int r, Mod a, Mod b, Mod x, Mod y) {
  std::vector<Mod> res{x, y};

  long gcd = 1;
  for (int i = 2; i < r; i++) {
    if (gcd != 1)
      return gcd;
    gcd = ECMultiply(a, b, res[0], res[1], i);
  }

  return gcd;
}

// To find a small prime factor of n:
// Maybe 100 times do the following
//    Choose xx, yy, A all random numbers between 1 and n.
//    Then solve B = yy^2 - xx^3 - A*xx mod n.
//    Let E be the elliptic curve y^2 = x^3 + A*x + B mod n and P be the point
//    (xx,yy). Note P is on E. We multiply r! * P on E mod n and hope that
//    something goes wrong along the way. Going "wrong" means that when trying
//    to do a modular inversion, one finds a gcd that is not 1 (or n). When that
//    happens, we want to pop out of this loop because we have a factor of n
//    (usually the smallest prime factor).
// End loop of 100 times if never found a factor

// Below are higher level functions. The first is ECFactor. It attempts to find
// a small prime factor of n using Lenstra's Elliptic Curve Method of
// factorization. I recommend r = 3000, tries = 100.
long ECFactor(long n, int r, int tries) {
  while (tries != 0) {
    tries--;
    std::vector<Mod> randEP = chooseEAndP(n);
    long gcd =
        findRFactorialPOnE(r, randEP[0], randEP[1], randEP[2], randEP[3]);
    if (gcd != 1)
      return gcd;
  }

  return 1;
}

// returns factorization using primes < 65521
std::vector<std::pair<long, int>> smallPrimeFactors(long &n) {
  std::vector<long>::iterator primePtr = smallPrimes.begin();
  std::vector<std::pair<long, int>> res;

  while (n > 1 || primePtr != smallPrimes.end()) {
    if (n % (*primePtr) == 0) {
      std::pair<long, int> factor(*primePtr, 1);
      n /= *primePtr;
      while (n % (*primePtr) == 0) {
        factor.second++;
        n /= *primePtr;
      }

      res.push_back(factor);
    }
    primePtr++;
  }

  return res;
}

std::pair<long, int> highPowers(long &n, long p) {
  std::pair<long, int> pfactor(p, 1);

  n /= p;
  while (n % p == 0) {
    n /= p;
    pfactor.second++;
  }

  return pfactor;
}

// returns array of pairs of (factor, power)
std::vector<std::pair<long, int>> factorize(long n) {
  if (n == 0)
    return std::vector<std::pair<long, int>>();
  n = std::abs(n);

  // remove small prime factors from n
  std::vector<std::pair<long, int>> factors = smallPrimeFactors(n);

  if (n == 1)
    return factors;

  while (n > 1) {
    long probablePrimeFactor = ECFactor(n, 3000, 200);

    if (probablePrimeFactor == 1)
      break;

    if (!millerRabin(probablePrimeFactor, 100)) {
      std::vector<std::pair<long, int>> primeFactors =
          factorize(probablePrimeFactor);
      for (std::pair<long, int> f : primeFactors) {
        factors.push_back(highPowers(f.first, n));
      }
    } else {
      factors.push_back(highPowers(n, probablePrimeFactor));
    }
  }

  return factors;
}

void FibProduct(std::vector<size_t> one, std::vector<size_t> two) {
  size_t x = 0;
  size_t y = 1;
  bool singleton = false;
  bool odd_factors = false;

  for (size_t i = 0; i < (size_t)pow(2, two.size()); ++i) {
    for (size_t j = 0; j < two.size(); j++) {
      if ((i & (1 << j)) != 0) {
        odd_factors = !(odd_factors);
        if (x == 0) {
          singleton = true;
          x = two[j];
        } else {
          singleton = false;
          x *= two[j];
        }
      }
    }

    if (singleton == false && odd_factors == true) {
      std::cout << x << " times: 1 = " << x << std::endl;
    }

    if (odd_factors == true) {
      for (size_t k = 1; k < (size_t)pow(2, one.size()); ++k) {
        y = 1;
        std::cout << x << " times: ";

        for (size_t l = 0; l < one.size(); l++) {
          if ((k & (1 << l)) != 0) {
            std::cout << one[l] << ", ";
            y *= one[l];
          }
        }

        std::cout << "= " << x << " times " << y << " = " << x * y << std::endl;
      }
    }
    std::cout << std::endl;

    x = 0;
    odd_factors = false;
  }
}
