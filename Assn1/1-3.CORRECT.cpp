#include <cstdio>
#include <cstdlib>

#define NO 0
#define YES 1

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    int* results = (int*) calloc (t, sizeof(int));
    for (int CASE=0; CASE<t; CASE++) {
        int N, C;
        scanf ("%d %d", &N, &C);
        int* lap = (int*) calloc (C, sizeof(int));
        int* hit = (int*) calloc (C, sizeof(int));
        int fullHit = -1;

        bool search_flag = true;
        for (int in=0; in<N*C; in++) {
            int input;
            scanf ("%d", &input);
            if (search_flag == true) {
                for (int i=fullHit+1; i<C; i++) {
                    // printf ("lap[%d]:%d ? input:%d\n", i, lap[i], input);
                    if (lap[i] == 0 || lap[i] == input) {
                        lap[i] = input;
                        if (++hit[i] == N)
                            fullHit++;
                        // printf (" %d hit!\n", hit[i]);
                        if (i>0 && hit[i-1] < hit[i]) {
                            // printf ("  but, %d's hit is %d.. YES!\n", i-1, hit[i-1]);
                            results[CASE] = YES;
                            search_flag = false;
                        }
                        break;
                    }
                }
            }
        }
        free (lap);
        free (hit);
    }
    for (int CASE=0; CASE<t; CASE++) {
        if (results[CASE] == YES)
            printf ("YES\n");
        else
            printf ("NO\n");
    }
    free (results);
}