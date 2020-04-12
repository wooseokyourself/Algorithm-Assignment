#include <cstdio>
#include <cstdlib>
#include <cmath>

#define UP      0
#define FIRST   1
#define RIGHT   2 
#define SECOND  3
#define DOWN    4
#define THIRD   5
#define LEFT    6
#define FOURTH  7

class Point {
private:
    int x;
    int y;
    double a; // y = ax

    int QUARD;

public:
    Point (int x, int y) : x(x), y(y) {
        if (x > 0 && y > 0)
            QUARD = FIRST;
        else if (x > 0 && y < 0)
            QUARD = SECOND;
        else if (x < 0 && y < 0)
            QUARD = THIRD;
        else if (x < 0 && y > 0)
            QUARD = FOURTH;
        else if (y > 0 && x == 0)
            QUARD = UP;
        else if (y == 0 && x > 0)
            QUARD = RIGHT;
        else if (y < 0 && x == 0)
            QUARD = DOWN;
        else if (y == 0 && x < 0)
            QUARD = LEFT;
        else {
            exit(-1);
        }
        

        // normalize
        if (QUARD == UP || QUARD == RIGHT || QUARD == DOWN || QUARD == LEFT)
            a = 0;
        else
            a = double(this->y)/double(this->x);
    }

    inline int getQ() { return QUARD; }
    inline void print() { printf ("%d %d\n", x, y); }

    bool operator== (const Point& pt) {
        if (this->QUARD == pt.QUARD)  
            return (this->x == pt.x && this->y == pt.y) ? true : false;
        else
            return false;
    }

    bool operator!= (const Point& pt) {
        if (this->QUARD != pt.QUARD)
            return true;
        else
            return (this->x != pt.x || this->y != pt.y) ? true : false;
    }

    bool operator < (const Point& pt) {
        if (this->QUARD != pt.QUARD)
            return (this->QUARD < pt.QUARD) ? true : false;
        else {
            if (pt.QUARD == FIRST || pt.QUARD == SECOND
                || pt.QUARD == THIRD || pt.QUARD == FOURTH) {
                if (this->a != pt.a)  // a가 작을수록 큼
                    return (pt.a < this->a) ? true : false;
                else {
                    if (pt.QUARD == FIRST || pt.QUARD == SECOND) // x가 클수록 큼
                        return (this->x < pt.x) ? true : false;
                    else if (pt.QUARD == THIRD || pt.QUARD == THIRD) // x가 작을수록 큼
                        return (pt.x < this->x) ? true : false;
                }
            }
            else if (pt.QUARD == UP) // y가 클수록 큼
                return (this->y < pt.y) ? true : false;
            else if (pt.QUARD == DOWN) // y가 작을수록 큼
                return (pt.y < this->y) ? true : false;
            else if (pt.QUARD == RIGHT) // x가 클수록 큼
                return (this->x < pt.x) ? true : false;
            else if (pt.QUARD == LEFT) // x가 작을수록 큼
                return (pt.x < this->x) ? true : false;
            else
                exit(-1);
        }
    }

    bool operator<= (const Point& pt) {
        if (this->QUARD != pt.QUARD)
            return (this->QUARD < pt.QUARD) ? true : false;
        else {
            if (pt.QUARD == FIRST || pt.QUARD == SECOND
                || pt.QUARD == THIRD || pt.QUARD == FOURTH) {
                if (this->a != pt.a) // a가 작을수록 큼
                    return (pt.a <= this->a) ? true : false;
                else {
                    if (pt.QUARD == FIRST || pt.QUARD == SECOND) // x가 클수록 큼
                        return (this->x <= pt.x) ? true : false;
                    else if (pt.QUARD == THIRD || pt.QUARD == THIRD) // x가 작을수록 큼
                        return (pt.x <= this->x) ? true : false;
                }
            }
            else if (pt.QUARD == UP) // y가 클수록 큼
                return (this->y <= pt.y) ? true : false;
            else if (pt.QUARD == DOWN) // y가 작을수록 큼
                return (pt.y <= this->y) ? true : false;
            else if (pt.QUARD == RIGHT) // x가 클수록 큼
                return (this->x <= pt.x) ? true : false;
            else if (pt.QUARD == LEFT) // x가 작을수록 큼
                return (pt.x <= this->x) ? true : false;
            else
                exit(-1);
        }
    }


    bool operator> (const Point& pt) {
        return (! (*this <= pt) ) ? true : false;
    }

    bool operator>= (const Point& pt) {
        return (! (*this < pt) ) ? true : false;
    }
};

void swap (Point* arr, int idx1, int idx2) {
    Point temp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = temp;
}

void insertion_sort (Point* arr, int start, int end) {
    for (int i=start+1; i<=end; i++) {
        Point k = arr[i];
        int j;
        for (j=i-1; j>=0; j--) {
            if (arr[j] > k)
                arr[j+1] = arr[j];
            else
                break;
        }
        arr[j+1] = k;
    }
    return ;
}


int divide (Point* arr, int a, int c) {
    int b = a + (c - a)/2;
    if (arr[b] <= arr[a] && arr[a] <= arr[c])
        return a;
    else if (arr[c] <= arr[a] && arr[a] <= arr[b])
        return a;
    else if (arr[a] <= arr[b] && arr[b] <= arr[c])
        return b;
    else if (arr[c] <= arr[b] && arr[b] <= arr[a])
        return b;
    else if (arr[a] <= arr[c] && arr[c] <= arr[b])
        return c;
    else if (arr[b] <= arr[c] && arr[c] <= arr[a])
        return c;
    else
        return c;
}

/* start = 배열의 첫번째 인덱스, end = 배열의 마지막 인덱스 
    힙정렬은 시행 안합니다! */
void intro_sort (Point* arr, int start, int end, int limit) {
    int len = end - start + 1;

    if (len <= 16) { // 배열의 사이즈가 16 이하면 삽입정렬 시행
        // printf ("   case) insertion_sort!\n");
        insertion_sort (arr, start, end);
        return;
    }

    // 이외에는 퀵정렬 시행

    int left = start;
    int right = end;
    if (left < right) {
        int p = divide (arr, left, right);
        Point pivot = arr[p];
        swap (arr, p, right);
        int store_idx = left;
        for (int i=left; i<right; i++) {
            if (arr[i] < pivot) {
                swap (arr, i, store_idx);
                store_idx++;
            }
        }
        swap (arr, store_idx, right);

        intro_sort (arr, left, store_idx-1, limit-1);
        intro_sort (arr, store_idx+1, right, limit-1);
    }
}

void sort (Point* arr, int start, int end) {
    int limit = 2 * log(end-start);
    intro_sort (arr, start, end, limit);
    return;
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    Point** results = (Point**) malloc (sizeof(Point*) * t);
    int* arrlen = (int*) malloc (sizeof(int) * t);
 
    // 입력받는 점을 각 사분면 밑 4개의 x,y축으로 구분하여 구분된 집합끼리 sort시킨뒤 병합
    for (int CASE=0; CASE<t; CASE++) {
        int n;
        scanf ("%d", &n);
        results[CASE] = (Point*) malloc (sizeof(Point) * n);
        arrlen[CASE] = n;
        // 8 pivots
        Point* UPs = (Point*) malloc (sizeof(Point) * n);
        Point* FIRSTs = (Point*) malloc (sizeof(Point) * n);
        Point* RIGHTs = (Point*) malloc (sizeof(Point) * n);
        Point* SECONDs = (Point*) malloc (sizeof(Point) * n);
        Point* DOWNs = (Point*) malloc (sizeof(Point) * n);
        Point* THIRDs = (Point*) malloc (sizeof(Point) * n);
        Point* LEFTs = (Point*) malloc (sizeof(Point) * n);
        Point* FOURTHs = (Point*) malloc (sizeof(Point) * n);

        int UPi = 0;
        int FIRSTi = 0;
        int RIGHTi = 0;
        int SECONDi = 0;
        int DOWNi = 0;
        int THIRDi = 0;
        int LEFTi = 0;
        int FOURTHi = 0;

        for (int i=0; i<n; i++) {
            int x, y;
            scanf ("%d %d", &x, &y);
            Point pt (x, y);
            if (pt.getQ() == UP)            UPs[UPi++] = pt;
            else if (pt.getQ() == FIRST)    FIRSTs[FIRSTi++] = pt;
            else if (pt.getQ() == RIGHT)    RIGHTs[RIGHTi++] = pt;
            else if (pt.getQ() == SECOND)   SECONDs[SECONDi++] = pt;
            else if (pt.getQ() == DOWN)     DOWNs[DOWNi++] = pt;
            else if (pt.getQ() == THIRD)    THIRDs[THIRDi++] = pt;
            else if (pt.getQ() == LEFT)     LEFTs[LEFTi++] = pt;
            else if (pt.getQ() == FOURTH)   FOURTHs[FOURTHi++] = pt;
            else {
                printf ("error\n");
                exit(0);
            }
        }
        sort (UPs, 0, UPi-1);
        sort (FIRSTs, 0, FIRSTi-1);
        sort (RIGHTs, 0, RIGHTi-1);
        sort (SECONDs, 0, SECONDi-1);
        sort (DOWNs, 0, DOWNi-1);
        sort (THIRDs, 0, THIRDi-1);
        sort (LEFTs, 0, LEFTi-1);
        sort (FOURTHs, 0, FOURTHi-1);

        int idx = 0;
        for (int i=0; i<UPi; i++)
            results[CASE][idx++] = UPs[i];
        for (int i=0; i<FIRSTi; i++)
            results[CASE][idx++] = FIRSTs[i];
        for (int i=0; i<RIGHTi; i++)
            results[CASE][idx++] = RIGHTs[i];
        for (int i=0; i<SECONDi; i++)
            results[CASE][idx++] = SECONDs[i];
        for (int i=0; i<DOWNi; i++)
            results[CASE][idx++] = DOWNs[i];
        for (int i=0; i<THIRDi; i++)
            results[CASE][idx++] = THIRDs[i];
        for (int i=0; i<LEFTi; i++)
            results[CASE][idx++] = LEFTs[i];
        for (int i=0; i<FOURTHi; i++)
            results[CASE][idx++] = FOURTHs[i];
        
        free (UPs);
        free (FIRSTs);
        free (RIGHTs);
        free (SECONDs);
        free (DOWNs);
        free (THIRDs);
        free (LEFTs);
        free (FOURTHs);
    }

    printf ("\n");
    for (int CASE=0; CASE<t; CASE++) {
        for (int i=0; i<arrlen[CASE]; i++)
            results[CASE][i].print();
        printf ("\n");
        free (results[CASE]);
    }
    free (results);
    free (arrlen);
    
    return 0;
}