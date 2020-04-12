#include <stdio.h>
#include <stdlib.h>

int getResultsByBST (int* arr, int size, int target);

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    int** A = malloc (sizeof(int*) * t); // Array
    int** Q = malloc (sizeof(int*) * t); // Query
    int** R = malloc (sizeof(int*) * t); // Results
    int* query_size = malloc (sizeof(int) * t);
    for (int CASE=0; CASE<t; CASE++) {
        int n, m;
        scanf ("%d %d", &n, &m);
        query_size[CASE] = m;
        A[CASE] = malloc (sizeof(int) * n);
        Q[CASE] = malloc (sizeof(int) * m);
        R[CASE] = malloc (sizeof(int) * m);
        for (int i=0; i<n; i++)
            scanf ("%d", &(A[CASE][i]));

        for (int i=0; i<m; i++) {
            scanf ("%d", &(Q[CASE][i]));
            R[CASE][i] = getResultsByBST (A[CASE], n, Q[CASE][i]);
        }
    }

    for (int CASE=0; CASE<t; CASE++) {
        for (int i=0; i<query_size[CASE]; i++) {
            printf ("%d ", R[CASE][i]);
        }
        printf ("\n");
        free (A[CASE]);
        free (Q[CASE]);
        free (R[CASE]);
    }
    free (A);
    free (Q);
    free (R);
    free (query_size);

    return 0;
}

int getResultsByBST (int* arr, int size, int query) {
    int lastToken;
    int begin = 0;
    int end = size - 1;
    int mid;
    while (begin <= end) {
        mid = (begin + end) / 2;
        if (arr[mid] == query)
            return arr[mid];
        else if (arr[mid] > query) {
            end = mid - 1;
        }
        else { // arr[mid] < query
            begin = mid + 1;
        }
    }
    // In this point, there are two cases
    // A[mid-1] < query < A[mid] -> exception when mid=0
    // A[mid] < query < A[mid+1] -> exception when mid=size-1
    if (mid == 0)
        return abs(query-arr[mid]) <= abs(query-arr[mid+1]) ? arr[mid] : arr[mid+1];
    else if (mid == size-1)
        return abs(query-arr[mid-1]) <= abs(query-arr[mid]) ? arr[mid-1] : arr[mid];
    else {
        int prev = abs(arr[mid-1] - query);
        int curr = abs(arr[mid] - query);
        int next = abs(arr[mid+1] - query);
        int min = prev;
        if (curr < min)
            min = curr;
        if (next < min)
            min = next;
        if (min == prev)
            return arr[mid-1];
        else if (min == curr)
            return arr[mid];
        else
            return arr[mid+1];
    }
}