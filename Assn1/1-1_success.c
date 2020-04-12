/*
A+B
Description¶
Write a program that takes two integers  A  and  B  from the standard input(stdin) and print an integer  A+B  to the standard output(stdout).

Input Example
4
1 2
3 4
5 6
7 8

Output Example
3
7
11
15

Time Limit: 1 second
*/

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]) {
    int n;
    scanf ("%d", &n);
    int* ans = malloc (sizeof(int)*n);
    for (int i=0; i<n; i++) {
        int a, b;
        scanf ("%d", &a);
        scanf ("%d", &b);
        ans[i] = a + b;
    }

    for (int i=0; i<n; i++) {
        printf ("%d\n", ans[i]);
    }

    free (ans);
    return 0;
}