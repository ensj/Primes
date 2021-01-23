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

void FibProduct(vector<size_t> one, vector<size_t> two)
{
	size_t x = 0;
	size_t y = 1;
	bool singleton = false;
	bool odd_factors = false;


	for (size_t i = 0; i < (size_t) pow(2, two.size()); ++i) 
    {
        for (size_t j = 0; j < two.size(); j++) 
        { 
			if ((i & (1 << j)) != 0)
			{
				odd_factors = !(odd_factors);
				if (x == 0)
				{
					singleton = true;
					x = two[j];
				}
				else
				{
					singleton = false;
					x *= two[j];
				}
			}	
		}

		if(singleton == false && odd_factors == true)
		{
				cout << x << " times: 1 = " << x << endl;
		}

		if(odd_factors == true)
		{
			for (size_t k = 1; k < (size_t) pow(2, one.size()); ++k) 
			{
				y = 1;
				cout << x << " times: ";

				for (size_t l = 0; l < one.size(); l++) 
				{ 
					if ((k & (1 << l)) != 0)
					{
						cout << one[l] << ", ";
						y *= one[l];
					}
				}

				cout << "= " << x << " times " << y << " = " << x*y << endl;
			}
		}
		cout << endl;

		x = 0;
		odd_factors = false;
	}
}
