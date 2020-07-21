#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>

#define node int // <= 1,000
#define weight int // <= 10,000
#define MAX_WEIGHT 2147483646
#define get_dest first
#define get_weight second
#define Graph vector< vector< pair<node, weight> > >

using namespace std;

struct greater_weight {
    bool operator() (pair<node, weight> a, pair<node, weight> b) {
        return (a.get_weight > b.get_weight) ? true : false;
    }
};

void getResult (const int& CASE, vector< stack<node> >& results, const Graph& G) {
    weight* dist = new weight[G.size()];
    node* prev = new node[G.size()];
    for (int i=0; i<G.size(); i++) {
        dist[i] = MAX_WEIGHT;
        prev[i] = -1;
    }
    dist[0] = 0;
    priority_queue< pair<node, weight>, vector< pair<node, weight> >, greater_weight> pq;
    pq.push(make_pair(0, 0)); // 시작점은 node 0
    
    while (!pq.empty()) { // dijkstra
        // printf ("bfs!\n");
        node now = pq.top().get_dest;
        pq.pop();
        for (int i=0; i<G[now].size(); i++) { // 노드 now의 모든 인접노드에 대해
            // printf (" access adj!\n");
            node adj = G[now][i].get_dest;
            weight wght = G[now][i].get_weight;
            if (dist[adj] > dist[now] + wght) { 
                // printf ("   set dist!\n");
                dist[adj] = dist[now] + wght;
                prev[adj] = now;
                pq.push (G[now][i]);
            }
        }
    }

    node nav = G.size() - 1;
    while (prev[nav] != -1) {
        results[CASE].push (nav);
        nav = prev[nav];
    }
    if (!results[CASE].empty())
        results[CASE].push(0);

    delete[] dist;
    delete[] prev;
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    vector< stack<node> > results(t);
    for (int CASE=0; CASE<t; CASE++) {
        int N, M;
        scanf ("%d %d", &N, &M);
        Graph G (N);
        int u, v, c;
        for (int i=0; i<M; i++) {
            scanf ("%d %d %d", &u, &v, &c);
            G[u].push_back(make_pair(v, c));
        }
        getResult (CASE, results, G);
    }
    for (int CASE=0; CASE<t; CASE++) {
        if (results[CASE].size() == 0)
            printf ("NO\n");
        else {
            while (!results[CASE].empty()) {
                printf ("%d ", results[CASE].top());
                results[CASE].pop();
            }
            printf ("\n");
        }
    }
    return 0;
}