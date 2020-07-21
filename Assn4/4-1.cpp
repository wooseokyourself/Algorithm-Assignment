#include <cstdio>
#include <cstdlib>
#include <utility>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

#define fee long long
#define deadline int
#define P pair<fee, deadline>
class P_less {
public:
    bool operator() (P a, P b) {
        if (a.first < b.first)
            return true;
        else if (a.first == b.first && a.second >= b.second)
            return true;
        else
            return false;
    }    
};
#define max_heap_for_P priority_queue< P, vector<P>, P_less >
#define min_heap_for_P priority_queue< P, vector<P>, greater<P> >
#define min_heap_for_d priority_queue< deadline, vector<deadline>, greater<deadline> >


/*
    1. 입력받은 P를 f의 오름차순으로 정렬 (pq는 입력된 모든 P의 집합, f가 같으면 d가 작은 놈이 우선)
    2. 오름차순으로 정렬된 P에서 최대날짜(@max_d)만큼의 P를 f가 큰 순서대로 선택 
       (즉 선택된 녀석들의 수는 @max_d, 이녀석들은 f가 제일 큰 녀석들임)
    3. 선택된 녀석들의 f를 d값이 같은 놈들끼리 묶기. 이 집합은 s[d]이며,
       s[d]에는 선택된 놈들 중 deadline=d 인 녀석들의 f가 저장됨
    4. 각 그룹을 d가 작은 순서대로 순회하며(현재 d = i),
            (s[d=0].size + s[d=1].size + ... + s[d=i].size) <= i 라면 continue
            위 조건이 아니라면 s[i]에서 제일 작은 f를 하나 빼고,
                pq에서 선택되지 않은 놈들 중 f가 제일 큰 녀석을 하나 선택해서 알맞은 s[d]에 넣기
                이 새로 들어온 녀석의 deadline이 i보다 작다면 i=deadline, 이후 계속 순회
    5. 최종적으로 s의 모든 순회가 끝나면, s 내의 모든 집합에 저장된 f의 합이 result
*/

fee getResult (max_heap_for_P& pq, min_heap_for_d& ds) { // returns the maximum revenue we can take
    fee ret = 0;
    vector<int> idx; // deadline을 오름차순으로 가지고있는 배열
    // ex. @idx[0]=deadline 1, @idx[1]=deadline 2, @idx[2]=deadline 4, ...

    // idx 초기화
    idx.push_back (ds.top());
    ds.pop();
    while (!ds.empty()) {
        if (idx.back() != ds.top())
            idx.push_back (ds.top());
        ds.pop();
    }
    idx.push_back (-1); // deadline을 기준으로 sets를 순회한 뒤 끝을 인식하기 위함

    const deadline max_d = idx[idx.size() - 2]; // maximum deadline
    vector< min_heap_for_P > s(max_d + 1); // sets
    for (int i=0; i<max_d; i++) { // f가 제일 큰 녀석들을 최대날짜(@max_d)의 수만큼 선택
        deadline d = pq.top().second;
        s[d].push (pq.top()); // 선택된 녀석을 해당하는 set(@s[d]) 안에 넣기
        pq.pop();
        if (pq.empty())
            break;
    }
    int* prevSetsSize = (int*) calloc (max_d + 1, sizeof(int)); // @prevSetsSize[i] = @prevSetsSize[1] + ... + @prevSetsSize[i-1]
    int i=0;
    while(idx[i] != -1) { // sets(@s) 들을 순회
        if (prevSetsSize[idx[i]-1] + s[idx[i]].size() <= idx[i]) { // (이전 sets의 원소수 + 현재 set의 원소수) <= (현재 set의 deadline) 이라면
            // printf ("true! %d\n", idx[i]);
            prevSetsSize[idx[i]] = prevSetsSize[idx[i]-1] + s[idx[i]].size();
            i++;
        }
        else {
            // printf ("false! %d\n", idx[i]);
            // printf (" prevSetsSize[%d] = %d\n", idx[i]-1, prevSetsSize[idx[i]-1]);
            // printf ("  s[%d]'s min elem: %lld\n", idx[i], s[idx[i]].top().first);
            s[idx[i]].pop(); // 현재 set에서 가장 f가 낮은 녀석을 버리기
            if (!pq.empty()) {
                s[pq.top().second].push (pq.top()); // pq에서 선택되지 않은 녀석들 중 가장 f가 큰 녀석을 해당하는 set에 넣기
                // printf ("  pq's max elem: %d is pushed into s[%d]\n", pq.top(), d);
                if (idx[i] > pq.top().second) {  // 새로 들어온 녀석의 deadline이 현재 set의 deadline보다 작다면
                    while (i != pq.top().second) // 새로 들어온 녀석의 deadline을 가진 set부터 다시 순회
                        i--;
                }
                pq.pop();
            }
        }
    }
    for (int i=0; i<idx.size()-1; i++) {
        while (!s[idx[i]].empty()) {
            ret += s[idx[i]].top().first;
            s[idx[i]].pop();
        }
    }
    free (prevSetsSize);
    return ret;
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    fee* results = (fee*) malloc (sizeof(fee) * t);
    for (int CASE=0; CASE<t; CASE++) {
        int n; // number of bids
        scanf ("%d", &n);
        max_heap_for_P pq;
        min_heap_for_d ds;
        fee f;
        deadline d;
        for (int i=0; i<n; i++) {
            scanf ("%lld %d", &f, &d);
            pq.push (make_pair(f, d)); // f의 오름차순으로 정렬
            ds.push (d); // d의 내림차순으로 정렬
        }
        results[CASE] = getResult (pq, ds);
    }
    for (int CASE=0; CASE<t; CASE++)
        printf ("%lld\n", results[CASE]);
    free (results);
    return 0;
}