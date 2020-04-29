/*
    Locate Town Hall
    Input Example
    2
    10
    1 2 3 4 5 6 7 8 9 10
    10
    0 0 0 0 0 0 0 0 0 10000

    Output Example
    25
    10000
*/

#include <stdio.h>
#include <stdlib.h>

#define abs(x) ( ((x)<0)?-(x):(x) )

int findResult (int* h, int n);

int calcSumofDistance (int* h, int arrlen, int idx);

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    
    int* results = malloc (sizeof(int) * t);

    for (int i=0; i<t; i++) {
        int n;
        scanf ("%d", &n);
    
        // House location array 
        int* h = malloc (sizeof(int) * n);

        for (int i=0; i<n; i++)
            scanf ("%d", &h[i]);

        results[i] = findResult (h, n);
        
        free (h);
    }

    for (int i=0; i<t; i++)
        printf ("%d\n", results[i]);

    free (results);
    return 0;
}

int findResult (int* h, int n) {
    if (n == 0)
        return 0;

    // Results
    int* a = malloc (sizeof(int) * n);
    a[0] = calcSumofDistance (h, n, 0);
    int ret = a[0];
    for (int i=0; i<n-1; i++) {
        int x = (h[i+1] - h[i]) * (-n + 2*i + 2);
        a[i+1] = a[i] + x;

        if (ret >= a[i+1])
            ret = a[i+1];
    }

    

    free (a);
    return ret;
}

int calcSumofDistance (int* h, int arrlen, int idx) {
    int ret = 0;
    for (int i=0; i<arrlen; i++)
        ret += abs(h[i] - h[idx]);
    return ret;
}