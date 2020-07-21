#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

int getResult (vector<int>& arr, const int& size) {
    int ret = 1;
    vector<int> cache(size, 0);
    cache[size-1] = 1;
    for (int k=size-2; k!=-1; k--) {
        int j = k+1;
        while (j != size) {
            if (arr[k] < arr[j]) {
                if (cache[k] < cache[j] + 1) {
                    cache[k] = cache[j] + 1;
                }
            }
            j++;
        }
        if (cache[k] == 0) {
            cache[k] = 1;
        }

        if (ret < cache[k]) {
            ret = cache[k];
        }
    }
    return ret;
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    vector<int> results(t);

    for (int CASE=0; CASE<t; CASE++) {
        int n;
        scanf ("%d", &n);
        vector<int> inp(n);
        for (int i=0; i<n; i++) {
            scanf ("%d", &inp[i]);
        }
        results[CASE] = getResult(inp, n);
    }
    for (int CASE=0; CASE<t; CASE++) {
        printf ("%d\n", results[CASE]);
    }
    return 0;
}