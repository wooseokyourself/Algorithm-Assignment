// based on bellman-ford algorithm

#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>
#include <list>

#define weight long long
#define MIN_WEIGHT -9223372036854775808
#define MAX_WEIGHT 9223372036854775807

using namespace std;

class graph {
private:
    class _node_info {
        friend class graph;
    private:
        vector< pair<int, weight> > adjs;
        weight dist; // 시작점 g[0]으로부터 이 노드까지의 shortest length
        int len; // 시작점 g[0]으로부터 이 노드까지의 경로길이
        // int update_round; // 벨만포드 알고리즘에서 몇 번째 update 호출인지를 저장
        bool negativeCycle; // negative cycle 안에 포함되는가?
    public:
        _node_info () : dist(MAX_WEIGHT), len(0), negativeCycle(false) {}
        inline int adjsNum() { return adjs.size(); }
        inline void push_back (const int& v, const weight& w) { adjs.push_back (make_pair(v, w)); }
        inline void set_dist (const weight& d) { this->dist = d; }
        inline weight get_dist () { return this->dist; }
        inline int get_len () { return this->len; }
        inline void set_negative_cycle () { this->negativeCycle = true; }
        inline void refresh_round () { // 벨만포드 update의 한 회차가 끝나면 호출
            if (!negativeCycle)
                this->len = 0;
            // negative cycle이면 dist는 현재 len에서 최대한 줄어든 상태니 len도 남겨두기
        }
        inline void update (const weight& parent_dist, const weight& w, const int& path_len) {
            dist = min (this->dist, parent_dist + w);
            if (this->len == 0) // 이미 저장된 len이 없다면 부모의 len을 따르기
                this->len = path_len;
            // 이미 저장된 len이 있다면 그 len 유지 (그래프상에서 이 len을 만족해야 현재 저장된 dist를 얻을 수 있으므로)
        }
        inline pair<int, weight>& operator[] (const int& idx) { return adjs[idx]; }
    };
private:
    vector<_node_info> g;
public:
    graph (const int& V) { g.resize(V); }
    inline void add_edge (const int& start, const int& end, const weight& w) {
        g[start].push_back (end, w);
    }
    inline int size () { return this->g.size(); }
    inline _node_info& operator[] (const int& idx) { return this->g[idx]; }
    
};

vector<int> find_negative_cycles (graph& G) {
    weight ret = MAX_WEIGHT;
    int n = G.size();
    G[0].set_dist (0);
    vector<int> target; // negative cycle인 녀석들을 저장 
    vector<weight> last_updated(n);
    for (int BELLMAN_FORD_ROUND=0; BELLMAN_FORD_ROUND<n; BELLMAN_FORD_ROUND++) {
        for (int i=0; i<n; i++)
            G[i].refresh_round();
        for (int i=0; i<n; i++) { // 모든 노드에 대해
            weight par_dist = G[i].get_dist();
            int par_len = G[i].get_len();
            for (int j=0; j<G[i].adjsNum(); j++) { // 모든 간선에 대해
                int adj = G[i][j].first;
                weight w = G[i][j].second;
                G[adj].update (par_dist, w, par_len + 1);
                if (BELLMAN_FORD_ROUND == n-1)
                    if (last_updated[i] > G[adj].get_dist()) {
                        printf (" gotcha! %d\n", adj);
                        target.push_back (adj);
                    }
            }
        }
        if (BELLMAN_FORD_ROUND == n-2) {
            for (int i=0; i<n; i++) {
                last_updated[i] = G[i].get_dist();
            }
        }
    }
    return target; 
}

weight getResult (graph& G, const int& k) {
    // 벨만-포드 알고리즘 기반
    weight ret = MAX_WEIGHT;
    int n = G.size();
    vector<int> negatives = find_negative_cycles (G);
    for (int i=0; i<n; i++)
        G[negatives[i]].set_negative_cycle();
    printf ("destination: %d\n", n-1);
    G[0].set_dist (0);

    for (int BELLMAN_FORD_ROUND=0; BELLMAN_FORD_ROUND<n; BELLMAN_FORD_ROUND++) {
        printf ("[ROUND %d]\n", BELLMAN_FORD_ROUND);
        for (int i=0; i<n; i++)
            G[i].refresh_round();
        for (int i=0; i<n; i++) { // 모든 노드에 대해
            weight par_dist = G[i].get_dist();
            int par_len = G[i].get_len();
            for (int j=0; j<G[i].adjsNum(); j++) { // 모든 간선에 대해
                int adj = G[i][j].first;
                weight w = G[i][j].second;
                printf (" %d ---%lld---> %d : update\n", i, w, adj);
                if (G[adj].get_len() <= k)
                    G[adj].update (par_dist, w, par_len + 1);
                if (adj == n-1 && (G[adj].get_len() != 0 && G[adj].get_len() <= k)) {
                    ret = ret <= G[adj].get_dist() ? ret : G[adj].get_dist();
                    printf (" destLen: %d\n", G[adj].get_len());
                    printf ("  dest: %lld\n", G[adj].get_dist());
                }
            }
        }
    }
    return ret;
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    vector<weight> results(t);
    for (int CASE=0; CASE<t; CASE++) {
        int V, E, k;
        scanf ("%d %d %d", &V, &E, &k);
        graph G (V);
        for (int i=0; i<E; i++) {
            int u, v;
            weight w;
            scanf ("%d %d %lld", &u, &v, &w);
            G.add_edge (u, v, w);
        }
        results[CASE] = getResult (G, k);
    }
    for (int CASE=0; CASE<t; CASE++)
        printf ("%lld\n", results[CASE]);
    return 0;
}