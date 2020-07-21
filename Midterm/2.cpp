#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>

#define MAX_WEIGHT 2147483646
#define node int
#define weight int
#define Edges priority_queue<Edge, vector<Edge>, greater_weight>
#define Nodes vector<Node_WithSet>
#define Set unordered_set<node>

using namespace std;

struct Edge {
    pair<node, node> ns;
    weight w;
};

class Node_WithSet {
public:
    node n;
    Set s; // 노드 n이 담긴 집합
public:
    void set_n (node _n) {
        this->n = _n;
    }
    void set_s (Set _s) {
        this->s = _s;
    }
    Set get_set () {
        return this->s;
    }
};

struct greater_weight {
    bool operator() (Edge a, Edge b) {
        return (a.w > b.w) ? true : false;
    }
};

void merge_set (const int& u, const int& v, Nodes& n) {
    if (n[u].s.size() >= n[v].s.size()) {
        n[u].s.insert (n[v].s.begin(), n[v].s.end());
        Set merged = n[u].s;
        Set::iterator i;
        for (i=merged.begin(); i!=merged.end(); i++)
            n[*i].set_s(merged);
    }
    else {
        n[v].s.insert (n[u].s.begin(), n[u].s.end());
        Set merged = n[v].s;
        Set::iterator i;
        for (i=merged.begin(); i!=merged.end(); i++)
            n[*i].set_s(merged);
    }
}

weight kruskal (Nodes n, Edges e, int K) { // kruskal
    weight ret = 0;
    weight prev_w = e.top().w + K + 1;
    while (!e.empty()) {
        Edge l = e.top();
        e.pop();
        if (abs(prev_w - l.w) < K)
            continue;
        node u = l.ns.first;
        node v = l.ns.second;
        if (n[u].get_set() != n[v].get_set()) {
            ret += l.w;
            merge_set (u, v, n);
            prev_w = l.w;
        }
    }
    if (n[0].s.size() != n.size())
        return -1;
    else
        return ret;
}

weight getResult (Nodes n, Edges e, int K) { 
    weight min_w = e.top().w;
    priority_queue< weight, vector<weight>, greater<weight> > rets;
    rets.push(kruskal (n, e, K));
    while (rets.top() != -1) {
        e.pop();
        if (e.top().w - min_w >= K)
            break;
        else
            rets.push(kruskal (n, e, K));
    }
    return rets.top();
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    vector< weight > results(t);
    for (int CASE=0; CASE<t; CASE++) {
        int N, M, K;
        scanf ("%d %d %d", &N, &M, &K);
        Nodes n(N);
        // vector<Set*> memory_box (n.size()); // 종료직전 동적할당된 set들을 한 번에 해제하기위함
        for (int i=0; i<N; i++) {
            Set init_set;
            init_set.insert (i);
            n[i].set_n (i);
            n[i].set_s (init_set);
            // memory_box[i] = init_set;
        }
        Edges e;
        Edge inp;
        for (int i=0; i<M; i++) {
            scanf ("%d %d %d", &(inp.ns.first), &(inp.ns.second), &(inp.w));
            e.push (inp);
        }
        results[CASE] = getResult (n, e, K);
        // for (int i=0; i<n.size(); i++)
           // delete memory_box[i];
    }
    for (int CASE=0; CASE<t; CASE++) {
        if (results[CASE] == -1)
            printf ("NO\n");
        else {
            printf ("%d\n", results[CASE]);
        }
    }
    return 0;
}