#include <cstdio>
#include <cstdlib>
#include <climits>
#include <bitset>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

static int ans;
static bitset<12> ALL_VISIT;

void recursive_call (const int& N, const vector< vector<int> >& D, int start, int last, bitset<12> visited, int searched_dist) {
    visited.set(last, 1); // 방문표시
    // printf ("Now $(last): %d\n", last);
    // cout << "visited: " << visited << " | ALL_VISIT: " <<  ALL_VISIT << endl;
    if (visited == ALL_VISIT) { // 모든 노드가 방문되었으면
        if (D[last][start] != -1) { // last가 start와 연결되어있으면
            // printf (" go back!\n");
            ans = min (ans, searched_dist + D[last][start]);
        } // 모든 노드가 방문되었지만 last와 start가 연결되어있지 않다면 문제조건에 맞지 않는 케이스
        return;
    }
    for (int i=0; i<N; i++) { // i는 노드
        // cout << "last: " << last << ", i: " << i << endl;
        if (visited.test(i) == 0 && D[i][last] != -1) { // i 미방문 및 i가 last와 연결되어있다면
            recursive_call (N, D, start, i, visited, searched_dist + D[last][i]);
        } 
    }
    // cout << " end for!" << endl;
}

bool calcResult (const int& N, int M, const vector< vector<int> >& D) {
    bitset<12> visited; // 0은 미방문, 1은 방문을 의미
    visited.set(); // 사용안하는 구간을 1로 설정하기 위해 우선 모든 비트를 1로 설정
    for (int i=0; i<N; i++) { // 사용할 구간만 0으로 설정(미방문표시)
        visited.set(i, 0);
    }
    ans = INT_MAX;
    recursive_call (N, D, 0, 0, visited, 0);
    return ans == INT_MAX ? false : true;
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    vector<int> results (t);
    ALL_VISIT.set(); // 전체 비트를 1로 셋팅
    for (int CASE=0; CASE<t; CASE++) {
        int N, M;
        scanf ("%d %d", &N, &M);
        // graph g(N);
        vector< vector<int> > D (N, vector<int>(N, -1)); // 각 노드간 거리를 저장하는 2차원배열
        for (int i=0; i<M; i++) {
            int u, v, c;
            scanf ("%d %d %d", &u, &v, &c);
            // g[u].push_back(make_pair(v, c));
            D[u][v] = c;
            D[v][u] = c;
        }
        if (calcResult(N, M, D))
            results[CASE] = ans;
        else
            results[CASE] = -1;
    }
    for (int CASE=0; CASE<t; CASE++) {
        printf ("%d\n", results[CASE]);
    }
    return 0;
}