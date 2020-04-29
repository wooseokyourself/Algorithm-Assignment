#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>

#define graph vector<Node>

using namespace std;

class Node {
private:
    vector< pair<int, int> > _children; // 자식들, <자식노드번호, 가중치>
    vector< pair<int, int> > _parents; // 부모들, <부모노드번호, 가중치>
    bool hasPar; // 부모가 있는가?
    bool _isLeaf;
public:
    Node () : hasPar(false), _isLeaf(true) { }// { _parents.push_back(make_pair(-1, -1)); /*level을 카운트하기위함*/ }
    void insertChild (int child, int weight) {
        this->_children.push_back(make_pair(child, weight));
    }
    void insertParent (int par, int weight) {
        this->_parents.push_back(make_pair(par, weight));
    }
    void setParTrue () {
        hasPar = true;
    }
    void setLeafFalse () {
        _isLeaf = false;
    }
    inline bool hasParent() { return hasPar; }
    inline bool isLeaf() { return _isLeaf; }
    inline int childNum() { return _children.size(); }
    inline int parentNum() { return _parents.size(); }
    inline int getChild(int i) { 
        if (_children.size() <= i)
            return -1;
        else
            return _children[i].first;
    }
    inline int getParent(int i) {
        if (_parents.size() <= i)
            return -1;
        else
            return _parents[i].first;
    }
    inline int getForwardWeight(int i) {
        if (_children.size() <= i)
            return -1;
        else
            return _children[i].second;
    }
    inline int getBackwardWeight(int i) {
        if (_parents.size() <= i)
            return -1;
        else
            return _parents[i].second;
    }
};

using namespace std;

long long getResult (graph& G) {
    long long ret = 0;
    int n = G.size();
    vector<int> roots; // 루트녀석들의 번호
    vector<int> leaves; // leaf 녀석들의 반호
    vector<int> cache(n, -1); // idx --> leaf 의 경로중 최대값을 저장
    vector<int> dist(n, -1); // temporary로 쓰이는 dist

    for (int i=n; i<n; i++) { // Leaf녀석들 색출
        if (G[i].isLeaf())
            leaves.push_back (i);
    }
    
    
    for (int l=0; l<leaves.size(); l++) {
        queue<int> Q;
        Q.push(leaves[l]);
        cache[leaves[l]] = 0;
        int count = -1;
        while (!Q.empty()) {
            if (++count == leaves.size()/2)
                break;
            int now = Q.front();
            Q.pop();
            for (int i=0; i<G[now].parentNum(); i++) {
                int adj = G[now].getParent(i);
                Q.push (adj);
                cache[adj] = cache[now] + G[now].getBackwardWeight(i);
            }
        }
    }

    for (int i=0; i<n; i++) { // 루트녀석들 색출
        if (!G[i].hasParent())
            roots.push_back (i);
    }
    
    
    for (int r=0; r<roots.size(); r++) {
        queue<int> Q;
        Q.push(roots[r]);
        dist[roots[r]] = 0;
        
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            for (int i=0; i<G[now].childNum(); i++) {
                int adj = G[now].getChild(i);
                if (cache[adj] == -1) {
                    Q.push (adj);
                    dist[adj] = dist[now] + G[now].getForwardWeight(i);
                }
                else {
                    dist[adj] = dist[now] + cache[adj];
                }
                ret = dist[adj] > ret ? dist[adj] : ret;
            }
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
            G[u].insertChild(v, w);
            G[v].insertParent(u, w);
            if (!G[v].hasParent())
               G[v].setParTrue();
            if (G[u].isLeaf())
                G[u].setLeafFalse();
        }
        results[CASE] = getResult (G);
    }
    for (int CASE=0; CASE<t; CASE++)
        printf ("%lld\n", results[CASE]);
    return 0;
}