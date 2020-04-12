#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long getResult (long long* arr, int size) {
    long long end = 0;
    long long positive_max = 0; // range: (0 ~ 9,223,372,036,854,775,807]
    long long negative_max = LLONG_MIN; // range: [INT64_MIN ~ 0]
    for (int i=0; i<size; i++) {
        if (arr[i] <= 0 && negative_max < arr[i])
            negative_max = arr[i];
        end += arr[i];
        if (end < 0)
            end = 0;
        if (positive_max < end)
            positive_max = end;  
    }
    return (positive_max == 0 ? negative_max : positive_max);
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    long long* r = malloc (sizeof(long long) * t);
    for (int CASE=0; CASE<t; CASE++) {
        int n;
        scanf ("%d", &n);
        long long* arr = malloc (sizeof(long long) * n);

        for (int i=0; i<n; i++)
            scanf ("%lld", &arr[i]);
        r[CASE] = getResult (arr, n);
        free (arr);
    }
    for (int CASE=0; CASE<t; CASE++)
        printf ("%lld\n", r[CASE]);
    free (r);
    return 0;
}