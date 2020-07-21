#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

int getResult (vector< vector<int> >& g, const int& n, const int& m) {
    int ret = 0;
    vector< vector<int> > cache(n, vector<int>(m, -2000000000));
    cache[0][0] = g[0][0];
    /*
        여기에 구현
    */
    return ret;
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    vector<int> results(t);
    for (int CASE=0; CASE<t; CASE++) {
        int n, m;
        scanf ("%d %d", &n, &m);
        vector< vector<int> > inp(n, vector<int>(m));
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                scanf ("%d", &inp[i][j]);
            }
        }
        results[CASE] = getResult(inp, n, m);
    }
    for (int CASE=0; CASE<t; CASE++) {
        printf ("%d\n", results[CASE]);
    }
    return 0;
}