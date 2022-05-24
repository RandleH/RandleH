
#include "../inc/rh_math.hpp"


namespace rh_math{

unsigned long comb ( unsigned long n, unsigned long r, bool* overflow ){
    if( n<r        ) return 0;
    if( n==r       ) return 1;
    if( r > (n>>1) ) r = n-r;
    if( overflow   ) *overflow = false;
    
    unsigned long res = 1, res_cpy = 1;
    for( unsigned long son=n-r+1, div=1; div<=r; div++, son++ ){
        res_cpy = res;
        res = res*son/div;
        if( res_cpy > res ){
            if( overflow!= nullptr )
                *overflow = true;
            return -1;
        }
    }
    return res;
}

unsigned long gcd  ( unsigned long a, unsigned long b                 ){
    if( b>a )  return gcd(b,a);
    
    if( b==0 ) return a;
    
    if( !(a&1) ){
        if( !(b&1) ) return (unsigned long)(gcd(a>>1, b>>1) <<1);
        else         return (unsigned long)(gcd(a>>1, b   )    );
    }else{
        if( !(b&1) ) return (unsigned long)(gcd(a   , b>>1)    );
        else         return (unsigned long)(gcd(a-b , b   )    );
    }
    return 0;
}

unsigned long lcm  ( unsigned long a, unsigned long b, bool* overflow ){
    if( a==0 || b==0 ) return 0;
    if( a==b         ) return a;
    if( b>a          ) return lcm(b,a,overflow);
    
    if( overflow!=nullptr ) *overflow = false;
    b/=gcd(a, b);
    
    if( b*a > ULLONG_MAX ){
        if( overflow!=nullptr ){
            *overflow = true;
        }
        return -1;
    }
    return b*a;
}

unsigned long fib  ( unsigned long n){
    if(n==0||n==1) return 1;
    int res = 0;
    int fnm1 = 1,fnm2 = 1;
    for (int i=2; i<=n; ++i) {
        res  = fnm1+fnm2;
        fnm2 = fnm1;
        fnm1 = res;
    }
    return res;
}

unsigned long tri2 ( int x1, int y1, int x2, int y2, int x3, int y3   ){
    unsigned long a = x1*y2+x2*y3+x3*y1;
    unsigned long b = y1*x2-y2*x3-y3*x1;
    return (a>b)? (a-b):(b-a);
}

}


