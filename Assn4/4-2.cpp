#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>

#define park_size long long
typedef struct _hull {
    long long l;
    long long r;
    long long y;
} hull;
class less_hull {
public:
    bool operator() (hull a, hull b) {
        if (a.y < b.y)
            return true;
        else if (a.y == b.y && a.l >= b.l)
            return true;
        else
            return false;
    }
};
// #define max_heap_for_y priority_queue<hull, vector<hull>, less_hull>

using namespace std;

long long recur_increase_left (const vector<hull>& arr, int i, const long long& std_y) {
    if (i == -1 || arr[i].y < std_y)
        return 0;
    else
        return (arr[i].r - arr[i].l) + recur_increase_left (arr, i-1, std_y);
}

long long recur_increase_right (const vector<hull>& arr, int i, const long long& std_y) {
    if (i == arr.size() || arr[i].y < std_y)
        return 0;
    else
        return (arr[i].r - arr[i].l) + recur_increase_right (arr, i+1, std_y);
}

park_size getResult (vector<hull>& arr, const long long& min_y, const long long& w) {
    park_size ret = w * min_y;
    // printf ("arr[arr.size()-1]'s = %lld\n", ret);
    for (int i=0; i<arr.size(); i++) {
        if (arr[i].y == min_y)
            continue;
        long long width = recur_increase_left (arr, i-1, arr[i].y) + (arr[i].r - arr[i].l) + recur_increase_right (arr, i+1, arr[i].y);
        long long height = arr[i].y;
        park_size size = width * height;
        // printf ("arr[%d]'s = %lld\n", i, size);
        if (size > ret)
            ret = size;
    }
    return ret;
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    park_size* results = (park_size*) malloc (sizeof(park_size) * t);
    for (int CASE=0; CASE<t; CASE++) {
        int n;
        long long w;
        scanf ("%d %lld", &n, &w);
        vector<hull> arr(n);
        int min_y = 1000001;
        for (int i=0; i<n; i++) {
            scanf ("%lld %lld %lld", &arr[i].l, &arr[i].r, &arr[i].y);
            if (arr[i].y < min_y)
                min_y = arr[i].y;
        }
        results[CASE] = getResult (arr, min_y, w);
    }
    for (int CASE=0; CASE<t; CASE++)
        printf ("%lld\n", results[CASE]);
    free (results);
    return 0;
}