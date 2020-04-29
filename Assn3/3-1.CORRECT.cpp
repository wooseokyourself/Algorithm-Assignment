#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>

#define MAX 1001

using namespace std;

int getShortestCycle (vector< vector<int> >& G) {
    int n = G.size();
    int shortest = MAX;
    queue<int> Q;
    for (int i=0; i<n; i++) {
        vector<int> dist(n, MAX);
        vector<int> prev(n, -1); // prev[i]는 탐색트리에서 i노드를 큐에 집어넣을 시점의 노드(now)를 저장
        Q.push(i);
        dist[i] = 0;
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            int adj;
            int adjNum = G[now].size();
            for (int adjIdx=0; adjIdx<adjNum; adjIdx++) {
                adj = G[now][adjIdx];
                if (dist[adj] == MAX) { // 탐색되지 않은 인접노드
                    Q.push (adj);
                    dist[adj] = dist[now] + 1;
                    prev[adj] = now;
                }
                else if (prev[adj] != now && prev[now] != adj) {
                    int len = dist[now] + dist[adj] + 1;
                    shortest = shortest < len ? shortest : len;
                }
            }
        }
    }
    return shortest != MAX ? shortest : -1;
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    vector<int> results(t);
    for (int CASE=0; CASE<t; CASE++) {
        int n; // nodes <= 1000
        int m; // edges <= 10000
        scanf ("%d %d", &n, &m);
        vector< vector<int> > G(n); // 1차원은 노드(idx로 구분), 2차원은 그 노드와 연결된 노드
        for (int i=0; i<m; i++) {
            int a, b;
            scanf ("%d %d", &a, &b); // a와 b 노드는 서로 연결되어있다
            G[a].push_back(b);
            G[b].push_back(a);
        }
        results[CASE] = getShortestCycle (G);
    }
    for (int CASE=0; CASE<t; CASE++)
        printf ("%d\n", results[CASE]);
    return 0;
}