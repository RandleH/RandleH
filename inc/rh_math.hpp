
#include <climits>

#ifndef RH_MATH_H
#define RH_MATH_H

namespace rh_math{

extern unsigned long comb ( unsigned long n, unsigned long r, bool* overflow=nullptr );
extern unsigned long gcd  ( unsigned long a, unsigned long b                         );
extern unsigned long lcm  ( unsigned long a, unsigned long b, bool* overflow=nullptr );
extern unsigned long fib  ( unsigned long n);


}

#endif

