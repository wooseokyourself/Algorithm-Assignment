#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>

#define MAX_FLOW 1000000
#define CAPACITY 1
#define Graph vector< vector<int> >

using namespace std;

int getResult (Graph& g, int s, int t) { // returns max flow from s to t in g
    int ret = 0;
    vector<int> d (g.size(), -1); // 방문여부
    vector< vector<int> > f (g.size()); // flow
    for (int i=0; i<g.size(); i++) {
        f[i].assign(g.size(), 0);
    }
    // printf ("d[], flow[][] complete!\n");
    // f[a][b] == 노드 a에서 b로 가는 flow의 양
    while (true) {
        d.assign (g.size(), -1); // 방문여부 초기화
        queue<int> q;
        q.push (s);
        // printf ("BFS start...\n >> ");
        while (!q.empty()) { // bfs
            int now = q.front();
            // printf ("%d ", now);
            q.pop();
            for (int i=0; i<g[now].size(); i++) {
                int adj = g[now][i];
                if (CAPACITY - f[now][adj] > 0 && d[adj] == -1) { // 방문하지 않은 인접노드 중 흐름을 보낼 수 있는 경우
                    q.push(adj);
                    d[adj] = now;
                    if (adj == t)
                        break;
                }
            }
        }
        if (d[t] == -1)
            break;
        /*
        printf (" << \n");
        printf ("finding path: %d ", t);
        for (int i=t; d[i]!=s; i=d[i])
            printf ("%d ", d[i]);
        printf ("%d \n", s);
        */
        int min_flow = MAX_FLOW;
        for (int i=t; i!=s; i=d[i]) { // 최소 유량 탐색
            min_flow = (min_flow < (CAPACITY - f[d[i]][i]) ) ? min_flow : (CAPACITY - f[d[i]][i]);
        }
        // printf ("min_flow in this path: %d\n", min_flow);
        for (int i=t; i!=s; i=d[i]) {
            f[d[i]][i] += min_flow;
            f[i][d[i]] -= min_flow;
        }
        ret += min_flow;
    }
    return ret;
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    int* result = new int[t];
    for (int CASE=0; CASE<t; CASE++) {
        int n, m, l;
        scanf ("%d %d %d", &n, &m, &l);
        int nodes_num = n + m + 2;
        int s = 0;
        int t = nodes_num - 1; // source node, sink node
        Graph g(nodes_num); // make a flow graph
        // 인덱스가 노드의 번호, 저장된 값은 해당 노드의 인접노드들

        // source to n's nodes
        g[s].resize(n);
        for (int i=0; i<n; i++) {
            g[s][i] = i + 1; // n 내의 노드를 입력받았을 때, 그래프 내 실제 번호는 n + 1
        }
        // printf ("source --> [n] link complete!\n");
        // m's nodes to sink
        for (int i=0; i<m; i++) {
            g[i + n + 1].resize(1);
            g[i + n + 1][0] = t; // m 내의 노드를 입력받았을 때, 그래프 내 실제 번호는 m + n + 1
        }
        // printf ("[m] --> sink link complete!\n");

        // n's nodes to m's nodes
        for (int i=0; i<l; i++) {
            int from, to;
            scanf ("%d %d", &from, &to);
            from += 1;
            to += (n + 1);
            g[from].push_back(to);
        }

        result[CASE] = getResult (g, s, t);
    }
    for (int CASE=0; CASE<t; CASE++) {
        printf ("%d\n", result[CASE]);
    }
    delete[] result;
    return 0;
}