#include <cstdio>
#include <cstdlib>
#include <vector>

#define llong long long

using namespace std;

llong getResult (llong N, llong M) {
    vector<llong> cache (N+1);
    cache[(llong)0] = 1;
    if (N == 0)
        return 0%M;
    cache[(llong)1] = 1;
    if (N == 1)
        return 1%M;
    cache[(llong)2] = 2;
    if (N == 2)
        return 2%M;
    for (llong i=3; i<N+1; i++)
        cache[i] = (cache[i-3] + cache[i-2] + cache[i-1]) % M;
    llong ret = cache[N];
    return ret;
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    vector<llong> results(t);
    for (int CASE=0; CASE<t; CASE++) {
        llong N, M;
        scanf ("%lld %lld", &N, &M);
        results[CASE] = getResult(N, M);
    }
    for (int CASE=0; CASE<t; CASE++)
        printf ("%lld\n", results[CASE]);
    return 0;
}