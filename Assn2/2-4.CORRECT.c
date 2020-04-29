#include <stdio.h>
#include <stdlib.h>

#define false 0
#define true 1
#define bool int
#define uint unsigned int

#define is_archromatic(c) (c.r == c.g && c.g == c.b) ? true : false

struct rgb {
    uint r;
    uint g;
    uint b;
};

struct rgb merge_rgb (struct rgb a, struct rgb b, struct rgb c) {
    struct rgb ret;
    bool all_arch_flag = true;
    if (is_archromatic(a) == true) {
        ret.r = a.r;
    }
    else {
        ret.r = (a.r + a.g + a.b)%16;
        all_arch_flag = false;
    }
    if (is_archromatic(b) == true) {
        ret.g = b.g;
    }
    else {
        ret.g = (b.r + b.g + b.b)%16;
        all_arch_flag = false;
    }
    if (is_archromatic(c) == true) {
        ret.b = c.b;
    }
    else {
        ret.b = (c.r + c.g + c.b)%16;
        all_arch_flag = false;
    }
    if (all_arch_flag == true) {
        ret.g = 15;
    }
    return ret;
}


struct rgb merge_list_of_rgb (struct rgb* arr, int size) {
    int div = size/3;
    if (div <= 1) {
        struct rgb r = arr[0];
        struct rgb g = arr[1];
        struct rgb b = arr[2];
        free (arr);
        return merge_rgb (r, g, b);
    }
    struct rgb* ret = malloc (sizeof(struct rgb) * div);
    bool all_arch_flag = true;
    for (int i=0; i<size; i+=3) {
        ret[i/3] = merge_rgb (arr[i], arr[i+1], arr[i+2]);
    }
    free (arr);
    return merge_list_of_rgb (ret, div);
}

int main (int argc, char* argv[]) {
    int t;
    struct rgb* results;
    scanf ("%d", &t);
    results = malloc (sizeof(struct rgb) * t);
    for (int CASE=0; CASE<t; CASE++) {
        int k;
        scanf ("%d", &k);
        
        if (k == 1) {
            scanf ("%1X%1X%1X", &results[CASE].r, &results[CASE].g, &results[CASE].b);
            continue;
        }
        else {
            struct rgb* to_be_list = malloc (sizeof(struct rgb) * k);
            for (int i=0; i<k; i++) {
                scanf ("%1X%1X%1X", &to_be_list[i].r, &to_be_list[i].g, &to_be_list[i].b);
            }
            results[CASE] = merge_list_of_rgb (to_be_list, k);
        }
        
    }
    for (int CASE=0; CASE<t; CASE++)
        printf ("%X%X%X\n", results[CASE].r, results[CASE].g, results[CASE].b);
    free (results);
    return 0;
}