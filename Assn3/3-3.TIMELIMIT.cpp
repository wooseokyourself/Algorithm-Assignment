#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>
#include <list>

#define weight long long
#define MIN_WEIGHT -9223372036854775808
#define MAX_WEIGHT 9223372036854775807

using namespace std;

class path {
public:
    weight w;
    int len;
public:
    path () : w(0), len(0) { }
    inline void add_path (const weight inpW) {
        this->w += inpW;
        this->len++;
    }
    inline path clone() { return *this; }
    inline void set_remove_flag() { this->len = -1; } // 이후 리스트에서 len = -1 인 녀석은 제거됨
    inline bool isRemoved() { return this->len == -1 ? true : false; }
    inline const bool operator < (const path& cmp) { return this->w < cmp.w ? true : false; }
    inline const bool operator <= (const path& cmp) { return this->w <= cmp.w ? true : false; }
    inline const bool operator > (const path& cmp) { return this->operator < (cmp) == true ? false : true; }
    inline const bool operator >= (const path& cmp) { return this->operator <= (cmp) == true ? false : true; }
};

class graph {
private:
    class forwards {
        friend class graph;
    private:
        vector< pair<int, weight> > adjs;
        int short_len_to_dest; // 현재노드부터 dest까지의 최소거리
    public:
        forwards () : short_len_to_dest(3001) {}
        forwards (const int& v, const int& w) { adjs.push_back (make_pair(v, w)); }
        inline void set_short_len (const int& l) { this->short_len_to_dest = l; }
        inline int get_short_len () { return this->short_len_to_dest; }
        inline int adjsNum() { return adjs.size(); }
        inline void push_back (const int& v, const int& w) { adjs.push_back (make_pair(v, w)); }
        inline pair<int, weight>& operator[] (const int& idx) { return adjs[idx]; }
    };
    class backwards {
        friend class graph;
    private:
        vector< pair<int, weight> > adjs;
    public:
        backwards () {}
        backwards (const int& v, const int& w) { adjs.push_back (make_pair(v, w)); }
        inline int adjsNum() { return adjs.size(); }
        inline void push_back (const int& v, const int& w) { adjs.push_back (make_pair(v, w)); }
        inline pair<int, weight>& operator[] (const int& idx) { return adjs[idx]; }
    };
private:
    vector<forwards> g;
    vector<backwards> _g;
public:
    graph (const int& V) { g.resize(V), _g.resize(V); }
    inline void add_edge (const int& start, const int& end, const weight& w) {
        g[start].push_back (end, w);
    }
    inline int size () { return this->g.size(); }
    inline forwards& operator[] (const int& idx) { return this->g[idx]; }

    inline void add_back_edge (const int& start, const int& end, const weight& w) {
        _g[end].push_back (start, w);
    }
    inline backwards& getback(const int& idx){ return this->_g[idx]; }
};

void explore (graph& G, const int& idx, const int& dest, const int& k, weight& ret, path& p) {
    // pre-active
    if (idx == dest) { // 현재노드가 dest라면
        ret = ret <= p.w ? ret : p.w; // ret값 갱신
        p.set_remove_flag(); // path 폐기
        return;
    }

    list<path> paths;
    paths.push_back(p); // 인접노드 중 첫 번째 노드로의 탐색이 기존의 path를 그대로 유지, 나머지는 복사로 할당
    int adjsNum = G[idx].adjsNum();

    if (adjsNum == 0) { // leaf일 경우 (막다른길)
        p.set_remove_flag();
        return;
    }
    
    else {
        // 이하 adjs == 1, adjs >= 2 공통수행
        path temp_path = p.clone();
        
        int adj = G[idx][0].first;
        weight w = G[idx][0].second;
        p.add_path (w);
        if (G[adj].get_short_len() + p.len <= k)
            explore (G, adj, dest, k, ret, p);
        else { // (adj로부터 dest까지의 가장 빠른 경로 + 현재 path의 길이) 가 k보다 크다면 탐색할 필요 없음
            p.set_remove_flag();
            return;
        }

        if (adjsNum >= 2) { // 분기점일 경우 dfs
            for (int i=1; i<G[idx].adjsNum(); i++) {
                path new_path = temp_path.clone();
                paths.push_back (new_path);

                adj = G[idx][i].first;
                w = G[idx][i].second;
                // idx --w--> adj
                new_path.add_path (w);
                if (G[adj].get_short_len() + new_path.len <= k)
                    explore (G, adj, dest, k, ret, new_path);
                else {
                    paths.pop_back();
                    continue;
                }
                    
            }
        }
    }

    // post-active
    list<path>::iterator itr;
    for (itr = paths.begin(); itr != paths.end(); itr++) {
        if ((*itr).isRemoved()) {
            paths.erase(itr++);
        }
    }
}

void dijkstra (graph& G, const int& dest) {
    // dfs에서 불필요한 탐색을 막기 위해 각 노드별로 dest까지의 최단엣지수를 미리 구해두기
    int n = G.size();
    vector<int> dist(n, 3001);
    dist[n-1] = 0;
    queue<int> Q;
    Q.push (n-1);
    while (!Q.empty()) {
        int now = Q.front();
        Q.pop();
        for (int i=0; i<G.getback(now).adjsNum(); i++) {
            int adj = G.getback(now)[i].first;
            if (dist[adj] == 3001) {
                dist[adj] = dist[now] + 1;
                Q.push(adj);
            }
        }
    }
    for (int i=0; i<n; i++)
        G[i].set_short_len(dist[i]);
}

weight getResult (graph& G, const int& k) {
    weight ret = MAX_WEIGHT;
    path p;
    int dest = G.size()-1;
    dijkstra (G, dest);
    explore (G, 0, dest, k, ret, p);
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
            G.add_back_edge (u, v, w);
        }
        results[CASE] = getResult (G, k);
    }
    for (int CASE=0; CASE<t; CASE++)
        printf ("%lld\n", results[CASE]);
    return 0;
}