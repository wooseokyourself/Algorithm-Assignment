#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>

#define MAX_FLOW 1000000
#define CAPACITY 1
#define Graph vector< vector<int> >

using namespace std;

int getResult (Graph& g, Graph& c, int s, int t) { // returns max flow from s to t in g
    int ret = 0;
    vector<int> d (g.size(), -1); // 방문여부
    vector< vector<int> > f (g.size()*2, vector<int>(g.size()*2, 0));
    // flow: f[i][i+g.size()]가 순흐름, f[i+g.size()][i]가 역흐름을 의미

    // printf ("d[], flow[][] complete!\n");
    // f[a][b] == 노드 a에서 b로 가는 flow의 양
    while (true) {
        d.assign (g.size(), -1); // 방문여부 초기화
        queue<int> q;
        q.push (s);
        printf ("BFS start...\n >> \n");
        while (!q.empty()) { // bfs
            int now = q.front();
            printf (" now: %d, c[%d][%d]=%d | f[%d][%d]=%d\n", now, now, now, c[now][now], now, now+g.size(), f[now][now+g.size()]);
            q.pop();
            // if (c[now][now] - f[now][now+g.size()] > 0) // 현재 노드에 흐름을 보낼 수 있다면
            for (int i=0; i<g[now].size(); i++) {
                int adj = g[now][i];
                printf ("in BFS, now=%d, adj=%d\n", now, adj);
                if ( (c[now][adj] - f[now][adj] > 0) && (d[adj] == -1) ) {
                // 방문하지 않은 인접노드 중 흐름을 보낼 수 있는 경우
                    if (now!=adj) {
                        q.push(adj);
                        d[adj] = now;
                    }
                    printf ("d[%d] <-- %d\n", adj, now);
                    if (adj == t)
                        break;
                }
            }

        }
        printf ("exit flag== d[t]=%d\n", d[t]);
        if (d[t] == -1)
            break;
        
        printf (" << \n");
        printf ("finding path: %d ", t);
        for (int i=t; d[i]!=s; i=d[i])
            printf ("%d ", d[i]);
        printf ("%d \n", s);
        
        int min_flow = MAX_FLOW;
        for (int i=t; i!=s; i=d[i]) { // 최소 유량 탐색
            min_flow = (min_flow < (c[d[i]][i] - f[d[i]][i]) ) ? min_flow : (c[d[i]][i] - f[d[i]][i]); // 엣지의 capacity 
            min_flow = (min_flow < (c[i][i] - f[i][i+g.size()]) ) ? min_flow : (c[i][i] - f[i][i+g.size()]); // 노드의 capacity
        }
        printf ("min_flow in this path: %d\n", min_flow);
        for (int i=t; i!=-1; i=d[i]) {
            printf ("!!![i]=%d\n", i);
            // printf ("now i: %d / next i: %d\n", i, d[i]);
            if (i!=0) {
                f[d[i]][i] += min_flow; // 순방향간선 flow
                printf (" foward edge f[%d][%d]==%d\n", d[i], i, f[d[i]][i]);
                f[i][d[i]] -= min_flow; // 역방향간선 flow
            }
            f[i][i+g.size()] += min_flow; // 순방향 가상간선(노드) flow
            printf (" foward node f[%d][%d]==%d\n", i, i+g.size(), f[i][i+g.size()]);
            f[i+g.size()][i] -= min_flow; // 역방향 가상간선(노드) flow
            // printf ("end!\n");
        }
        ret += min_flow;
    }
    printf ("\n");
    return ret;
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    int* result = new int[t];
    for (int CASE=0; CASE<t; CASE++) {
        int n, m;
        scanf ("%d %d", &n, &m);
        Graph g (n);
        Graph c (n, vector<int>(n, 0)); // capacity, c[a][b] = a->b 간선의 cap
        for (int i=0; i<n; i++) { // input capacity of nodes
            scanf ("%d ", &c[i][i]);
            g[i].push_back (i);
        }
        for (int i=0; i<m; i++) { // input edges
            int from, to, cap;
            scanf ("%d %d %d", &from, &to, &cap);
            g[from].push_back (to); // 순간선
            g[to].push_back (from); // 역간선
            c[from][to] = cap;
        }

        result[CASE] = getResult (g, c, 0, n-1);
    }
    for (int CASE=0; CASE<t; CASE++) {
        printf ("%d\n", result[CASE]);
    }
    delete[] result;
    return 0;
}