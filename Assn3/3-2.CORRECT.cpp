#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>
#include <stack>

#define graph vector<Node>

#define gid int // graph id

using namespace std;

class Node {
private:
    vector< pair<int, int> > _children; // 자식들, <자식노드번호, 가중치>
public:
    void insertChild (gid child, int weight) {
        this->_children.push_back(make_pair(child, weight));
    }
    inline int childNum() { return _children.size(); }
    inline int getChild(int i) { 
        if (_children.size() <= i)
            return -1;
        else
            return _children[i].first;
    }
    inline int getFowradWeight(int i) {
        return _children[i].second;
    }
};

using namespace std;

void explore (graph& G, int idx, vector<long long>& cache, vector<bool>& visited, long long& ret) {
    gid now = idx;
    visited[idx] = true;
    for (int i=0; i<G[now].childNum(); i++) {
        gid adj = G[now].getChild(i);
        if (!visited[adj])
            explore (G, adj, cache, visited, ret);
        cache[now] = cache[now] > cache[adj] + G[now].getFowradWeight(i) ? cache[now] : cache[adj] + G[now].getFowradWeight(i);
        ret = ret > cache[now] ? ret : cache[now];
    }
}

long long getResult (graph& G) {
    long long ret = 0;
    int n = G.size();
    vector<long long> cache(n, 0);
    vector<bool> visited(n, false);
    for (int i=0; i<n; i++)
        if (!visited[i])
            explore (G, i, cache, visited, ret);
    return ret;
}

int main (int argc, char* argv[]) {
    // printf ("%lu\n", sizeof(Node)*3000);
    // printf ("%lu\n", sizeof(pair<int, int>)*100000);
    int t;
    scanf ("%d", &t);
    vector<long long> results(t);
    for (int CASE=0; CASE<t; CASE++) {
        int V; // nodes <= 3000
        int E; // edges <= 100000
        scanf ("%d %d", &V, &E);
        graph G(V);
        for (int i=0; i<E; i++) {
            int u, v, w; 
            scanf ("%d %d %d", &u, &v, &w);
            G[u].insertChild(v, w);
        }
        results[CASE] = getResult (G);
    }
    for (int CASE=0; CASE<t; CASE++)
        printf ("%lld\n", results[CASE]);
    return 0;
}