#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ull unsigned long long
#define mod(x) x%2147483647
#define logB(x, base) log(x)/log(base)
/*
    a(n+1) b(n  )
    b(n  ) c(n-1)
*/

struct matrix {
    ull a;
    ull b;
    ull c;
    ull d;
};

struct matrix cache[30]; // save base^(2^0) ~ base^(2^31)
int hit[30] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // 0 -> no / 1 -> yes

struct matrix mul (struct matrix m, struct matrix n) {
    struct matrix ret;
    
    ret.a = mod( mod(mod(m.a) * mod(n.a)) + mod(mod(m.b) * mod(n.c)) );
    ret.b = mod( mod(mod(m.a) * mod(n.b)) + mod(mod(m.b) * mod(n.d)) );
    ret.c = mod( mod(mod(m.c) * mod(n.a)) + mod(mod(m.d) * mod(n.c)) );
    ret.d = mod( mod(mod(m.c) * mod(n.b)) + mod(mod(m.d) * mod(n.d)) );
    /*
    ret.a = m.a*n.a + m.b*n.c;
    ret.b = m.a*n.b + m.b*n.d;
    ret.c = m.c*n.a + m.d*n.c;
    ret.d = m.c*n.b + m.d*n.d;
    */
    return ret;
}

/* returns m^(2^sq) */
struct matrix two_square_pow (struct matrix m, int sq) {
    if (sq == 0)
        return m;
    if (hit[sq] == 1) {
        return cache[sq];
    }
    else {
        struct matrix ret = m;
        for (int i=0; i<sq; i++)
            ret = mul (ret, ret);
        hit[sq] = 1;
        cache[sq] = ret;
        return ret;
    }
}

long int matrixFib (long int th) {
    if (th == 0)
        return 0;
    else if (th == 1)
        return 1;
    else {
        th--;
        struct matrix base; // result = (base^(th-1)).a
        base.a = 1; // n = 2
        base.b = 1; // n = 1
        base.c = 1; // n = 1
        base.d = 0; // n = 0
        struct matrix zero;
        zero.a = 1;
        zero.b = 0;
        zero.c = 0;
        zero.d = 1;
        struct matrix retMat = zero;
        while (th > 0) {
            struct matrix eachMat;
            if (th == 1) {
                th -= 1;
                eachMat = base;
            }
            else {
                int sq = logB(th, 2);
                th -= pow(2, sq);
                eachMat = two_square_pow (base, sq);
            }
            retMat = mul (retMat, eachMat);
        }
        return mod(retMat.a);
    }
    
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    long int* r = malloc (sizeof(long int) * t);

    for (int CASE=0; CASE<t; CASE++) {
        long int th;
        scanf ("%li", &th);
        r[CASE] = matrixFib (th);
    }
    for (int CASE=0; CASE<t; CASE++)
        printf ("%li\n", r[CASE]);
    free (r);
    return 0;
}