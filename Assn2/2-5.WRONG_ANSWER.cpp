#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct line {
    int xl;
    int xr;
    int y;
};

struct compare {
    bool operator() (struct line& a, struct line& b) {
        return a.xl > b.xl;
    }
};

vector<struct line> merge_segment (vector<struct line> vec_l, vector<struct line> vec_r) {
    /*
    struct line& l = vec_l[vec_l.size()-1];
    struct line r;
    vector<struct line> new_r;
    int i=0, size=vec_r.size();
    while (i < size) {
        if (l.xr < vec_r[i].xl) { // 분리되어있으므로 그냥 리턴
            break;
        }
        // l.xr >= vec_r[i].xl 에 대해
        if (l.xr <= vec_r[i].xr) {
            vec_r[i].xl = l.xl;
            break;
        }
        if (l.y >= vec_r[i].y) {
            vec_r.erase(vec_r.begin() + i);
            size--;
        }
        else {
            if (new_r.size() > 0) {
                if (new_r.back().xl == vec_r[i].xl)
                    new_r.pop_back();
                else
                    new_r.back().xr = vec_r[i].xl;
            }
            new_r.push_back (vec_r[i]);
            struct line detached_l;
            detached_l.xl = vec_r[i].xr;
            detached_l.y = l.y;
            detached_l.xr = -1;
            new_r.push_back (detached_l);
            i++;
        }
    }
    vector<struct line> ret;
    if (i == 0) { // 완전히 분리된 두 벡터
        ret.reserve (vec_l.size() + vec_r.size());
        ret.insert (ret.end(), vec_l.begin(), vec_l.end());
        ret.insert (ret.end(), vec_r.begin(), vec_r.end());
        return ret;
    }

    if (new_r.size() > 0)
        if (new_r.back().xr == -1)
            new_r.back().xr = l.xr;

    // 이제 vec_r 의 [0, i) 는 모두 버리고 그자리에 new_r이 차례대로 들어가야 한다.
    for (int j=i-1; j<vec_r.size(); j++)
        new_r.push_back (vec_r[j]);

    // new_r[0].y 는 l.y보다 무조건 크다.
    l.xr = new_r[0].xl;
    ret.reserve (vec_l.size() + new_r.size());
    ret.insert (ret.end(), vec_l.begin(), vec_l.end());
    ret.insert (ret.end(), vec_r.begin(), vec_r.end());
    return ret;
    */
    
    struct line& l = vec_l[vec_l.size()-1];
    struct line& r = vec_r[0];
    vector<struct line> ret;
    // printf (" merge_segment ( (%d %d %d), (%d %d %d) )\n", l.xl, l.xr, l.y, r.xl, r.xr, r.y);
    if (l.xr < r.xl) {
        // printf ("  result: 0. no need to merge\n");
        ret.reserve(vec_l.size() + vec_r.size());
        // return vec_l[begin, end) + vec_r(begin, end)
        ret.insert (ret.end(), vec_l.begin(), vec_l.end());
        ret.insert (ret.end(), vec_r.begin(), vec_r.end());
        return ret;
    }
    vec_l.pop_back();
    if (l.y == r.y) { // 하나 생기는 경우
        struct line m;
        m.xl = l.xl;
        m.xr = l.xr > r.xr ? l.xr : r.xr;
        m.y = l.y;
        vec_l.push_back(m);
        // printf ("  result: 1. (%d %d %d)\n", m.xl, m.xr, m.y);
    }
    else if ((l.y > r.y) && (l.xr >= r.xr)) { // 하나 생기는 경우
        struct line m;
        m.xl = l.xl;
        m.xr = l.xr;
        m.y = l.y > r.y ? l.y : r.y;
        vec_l.push_back(m);
        // printf ("  result: 2. (%d %d %d)\n", m.xl, m.xr, m.y);
    }
    else if ((l.xl < r.xl) && (l.xr > r.xr) && (l.y < r.y)) { // 세 개 생기는 경우
        struct line m, n, o;
        m.xl = l.xl;
        m.xr = r.xl;
        m.y = l.y;
        n.xl = r.xl;
        n.xr = r.xr;
        n.y = r.y;
        o.xl = r.xr;
        o.xr = l.xr;
        o.y = l.y;
        vec_l.push_back(m);
        vec_l.push_back(n);
        vec_l.push_back(o);
        // printf ("  result: 3. (%d %d %d) (%d %d %d) (%d %d %d)\n", m.xl, m.xr, m.y, n.xl, n.xr, n.y, o.xl, o.xr, o.y);
    }
    else { // 두개 생기는 경우
        struct line m, n;
        if (l.xl == r.xl) {
            m.xl = l.xl;
            m.xr = l.y > r.y ? l.xr : r.xr;
            m.y = l.y > r.y ? l.y : r. y;

            n.xl = m.xr;
            n.xr = l.y > r.y ? r.xr : l.xr;
            n.y = l.y > r.y ? r.y : l.y;
        }
        else if (l.y < r.y) {
            m.xl = l.xl;
            m.xr = r.xl;
            m.y = l.y;

            n.xl = m.xr;
            n.xr = r.xr;
            n.y = r.y;
        }
        else if (l.y > r.y) {
            m.xl = l.xl;
            m.xr = l.xr;
            m.y = l.y;

            n.xl = m.xr;
            n.xr = r.xr;
            n.y = r.y;
        }
        else {
            // printf ("  shit! unexpected case!\n");
            exit(-1);
        }
        vec_l.push_back(m);
        vec_l.push_back(n);
        // printf ("  result: 4. (%d %d %d) (%d %d %d)\n", m.xl, m.xr, m.y, n.xl, n.xr, n.y);
    }
    ret.reserve(vec_l.size() + vec_r.size()-1);
    // return vec_l[begin, end) + vec_r(begin, end)
    ret.insert (ret.end(), vec_l.begin(), vec_l.end());
    ret.insert (ret.end(), vec_r.begin()+1, vec_r.end());
    return ret;
}

vector<struct line> divide_and_conquer (vector<struct line> vec){
    if (vec.size() == 1) {
        return vec;
    }
    else {
        int size = vec.size();
        vector<struct line> L, R;
        L.assign (vec.begin(), vec.begin()+size/2);
        R.assign (vec.begin()+size/2, vec.end());

        /*
        printf ("  >> input vector: \n    ");
        for (int i=0; i<vec.size(); i++) {
            printf ("(%d %d %d) ", vec[i].xl, vec[i].xr, vec[i].y);
        }
        printf ("\n");
        printf ("    >> divided L: \n      ");
        for (int i=0; i<L.size(); i++) {
            printf ("(%d %d %d) ", L[i].xl, L[i].xr, L[i].y);
        }
        printf ("\n");
        printf ("    >> divided R: \n      ");
        for (int i=0; i<R.size(); i++) {
            printf ("(%d %d %d) ", R[i].xl, R[i].xr, R[i].y);
        }
        printf ("\n");
        */
        return merge_segment (divide_and_conquer(L), divide_and_conquer(R));
    }
}



int main (void) {
    int t;
    scanf ("%d", &t);
    vector< vector<struct line> > results(t);
    for (int CASE=0; CASE<t; CASE++) {
        int n;
        scanf ("%d", &n);
        struct line inp;
        priority_queue<struct line, vector<struct line>, compare> pq;
        for (int i=0; i<n; i++) {
            scanf ("%d %d %d", &inp.xl, &inp.xr, &inp.y);
            pq.push (inp);
        }
        vector<struct line> temp;
        temp.resize(n);
        printf ("\n");
        for (int i=0; i<n; i++) {
            temp[i] = pq.top();
            pq.pop();
            // printf ("input: %d %d %d\n", temp[i].xl, temp[i].xr, temp[i].y);
        }
        printf ("\n");
        results[CASE] = divide_and_conquer (temp);
    }
    for (int CASE=0; CASE<t; CASE++)
        for (int i=0; i<results[CASE].size(); i++)
            printf ("%d %d %d\n", results[CASE][i].xl, results[CASE][i].xr, results[CASE][i].y);

    return 0;
}