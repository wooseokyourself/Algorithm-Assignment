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
    int id;
    int max_backwardWeight; // 부모와 연결된 edge중 가장 높은 가중치 저장
    gid max_backwardParent; // 가장 높은 가중치의 edge와 연결된 부모 저장
    bool hasPar; // 부모가 있는가?
public:
    Node () : hasPar(false) { max_backwardWeight=0; max_backwardParent=-1; }
    inline void setId (gid id) { this->id = id; }
    inline int getId () { return id; }
    void insertChild (gid child, int weight) {
        this->_children.push_back(make_pair(child, weight));
    }
    void setParTrue () {
        hasPar = true;
    }
    inline bool hasParent() { return hasPar; }
    inline int childNum() { return _children.size(); }
    inline int getChild(int i) { 
        if (_children.size() <= i)
            return -1;
        else
            return _children[i].first;
    }
    inline int getMaxBackwardWeight() { return max_backwardWeight; }
    inline int getMaxBackwardParent() { return max_backwardParent; }
    inline void setMaxBackward (gid par, int weight) {
        if (max_backwardWeight < weight) {
            max_backwardWeight = weight;
            max_backwardParent = par;
        }
    }
};

using namespace std;

void explore (graph& G, int idx, vector<bool>& visited, stack<int>& S) {
    gid now = idx;
    visited[idx] = true;
    for (int i=0; i<G[now].childNum(); i++) {
        gid adj = G[now].getChild(i);
        if (!visited[adj])
            explore (G, adj, visited, S);
    }
    S.push (idx);
}

// topological_sort는 G 내의 노드 하나가 주어지고, 그 노드를 시작점으로 longest path 를 찾는 문제에서만 유효하다.
vector<int> topological_sort (graph& G) {
    int n = G.size();
    vector<bool> visited (n, false);
    stack<int> S;
    for (int i=0; i<n; i++)
        if (!visited[i])
            explore (G, i, visited, S);

    vector<int> ret(n);
    printf ("\n");
    printf ("Topological: \n");
    for (int i=0; i<n; i++) {
        ret[i] = S.top();
        S.pop();

        printf ("%d ", ret[i]);
    }
    printf ("\n");
    return ret;
}

long long getResult (graph& G) {
    long long ret = 0;
    vector<int> linearized = topological_sort (G);
    int n = linearized.size();
    vector<long long> dist(n, -1); // linearized된 벡터와 동일한 인덱스
    for (int i=0; i<n; i++) {
        gid now = linearized[i];
        if (!G[now].hasParent())
            dist[now] = 0;
        else {
            dist[now] = dist[G[now].getMaxBackwardParent()] + G[now].getMaxBackwardWeight();
            ret = ret > dist[now] ? ret : dist[now];
        }
    }
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
            G[u].setId(u);
            G[u].insertChild(v, w);
            G[v].setMaxBackward(u, w);
            if (!G[v].hasParent())
                G[v].setParTrue();
        }
        results[CASE] = getResult (G);
    }
    for (int CASE=0; CASE<t; CASE++)
        printf ("%lld\n", results[CASE]);
    return 0;
}