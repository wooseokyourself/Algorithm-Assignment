#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#define speed long long
#define graph vector< vector<speed> >
#define idx pair<int,int>
#define _idx(x,y) make_pair(x,y)
/*
                    G[rows-1][cols]
                        |
                        |
G[rows][cols-1] --- G[rows][cols] --- G[rows][cols+1]
                        |
                        |
                    G[rows+1][cols]
*/
using namespace std;

class Graph {
private:
    graph G;
    graph maxSpd; // G[0][0]에서 출발하였을 때, 유지할 수 있는 최대속도를 저장
    vector< vector<bool> > pushed; // 큐에 들어간적이 있는놈인지 판별
    vector< vector<bool> > visited; // 탐색시 방문된적이 있는지 판별
    int row;
    int col;
public:
    Graph(int N, int M) : row(N), col(M) {
        G.resize(N);
        maxSpd.resize(N);
        pushed.resize(N);
        visited.resize(N);
        for (int i=0; i<N; i++) {
            G[i].resize(M);
            maxSpd[i].resize(M, 0);
            pushed[i].resize(M, false);
            visited[i].resize(M, false);
        }
    }
    inline void checkPush (const int n, const int m) { pushed[n][m] = true; }
    inline void checkPush (const idx k) { pushed[k.first][k.second] = true; }
    inline bool isPushed (const int n, const int m) { return pushed[n][m]; }
    inline bool isPushed (const idx k) { return pushed[k.first][k.second]; }

    inline void checkVisit (const int n, const int m) { visited[n][m] = true; }
    inline void checkVisit (const idx k) { visited[k.first][k.second] = true; }
    inline bool isVisited (const int n, const int m) { return visited[n][m]; }
    inline bool isVisited (const idx k) { return visited[k.first][k.second]; }

    inline speed getLimit (const int n, const int m) { // check boundary
        if (n < 0 || row <= n || m < 0 || col <= m)
            return -1;
        else
            return G[n][m];
    }
    inline speed getLimit (const idx k) { // check boundary
        if (k.first < 0 || row <= k.first || k.second < 0 || col <= k.second)
            return -1;
        else
            return G[k.first][k.second];
    }
    inline void assign (const int n, const int m, const speed value) { // no check boundary
        G[n][m] = value;
    }
    inline void assign (const idx k, const speed value) { // no check boundary
        G[k.first][k.second] = value;
    }
    inline void compare_set_MaxPath (const int n, const int m, const speed val) { // no check boundary
        maxSpd[n][m] = maxSpd[n][m] >= val ? maxSpd[n][m] : val;
        maxSpd[n][m] = maxSpd[n][m] < G[n][m] ? maxSpd[n][m] : G[n][m];
    }
    inline void compare_set_MaxPath (const idx k, const speed val) { // no check boundary
        maxSpd[k.first][k.second] = maxSpd[k.first][k.second] >= val
                                  ? maxSpd[k.first][k.second] : val;
        maxSpd[k.first][k.second] = maxSpd[k.first][k.second] < G[k.first][k.second]
                                  ? maxSpd[k.first][k.second] : G[k.first][k.second];
    }
    inline speed getMaxPath (const int n, const int m) { return maxSpd[n][m]; }
    inline speed getMaxPath (const idx k) { return maxSpd[k.first][k.second]; }
    inline int rows() { return row; }
    inline int cols() { return col; }
    vector<idx> getAdjs (const idx k) {
        vector<idx> ret;
        idx left (k.first, k.second-1);
        idx right (k.first, k.second+1);
        idx up (k.first-1, k.second);
        idx down (k.first+1, k.second);
        speed temp;

        temp = this->getLimit(right);
        if (temp != -1) {
            if (!visited[right.first][right.second])
                ret.push_back(right);
            else if (maxSpd[right.first][right.second] < maxSpd[k.first][k.second]) {
                ret.push_back(right);
                pushed[right.first][right.second] = false; // 다시 큐에 들어갈 기회 부여
            }
        }

        temp = this->getLimit(down);
        if (temp != -1) {
            if (!visited[down.first][down.second])
                ret.push_back(down);
            else if (maxSpd[down.first][down.second] < maxSpd[k.first][k.second]) {
                ret.push_back(down);
                pushed[down.first][down.second] = false;
            }
        }

        temp = this->getLimit(left);
        if (temp != -1) {
            if (!visited[left.first][left.second])
                ret.push_back(left);
            else if (maxSpd[left.first][left.second] < maxSpd[k.first][k.second]) {
                ret.push_back(left);
                pushed[left.first][left.second] = false;
            }
        }

        temp = this->getLimit(up);
        if (temp != -1) {
            if (!visited[up.first][up.second])
                ret.push_back(up);
            else if (maxSpd[up.first][up.second] < maxSpd[k.first][k.second]) {
                ret.push_back(up);
                pushed[up.first][up.second] = false;
            }
        }

        return ret;
    }
};

speed getResult (Graph& G) {
    int rows = G.rows();
    int cols = G.cols();
    G.compare_set_MaxPath(0, 0, G.getLimit(0, 0)); // 시작점은 (0,0)
    queue<idx> Q;
    Q.push (_idx(0, 0));
    while (!Q.empty()) {
        idx now = Q.front();
        Q.pop();
        G.checkVisit (now);
        vector<idx> adjs = G.getAdjs(now); // 접근한적없거나, 접근했지만 maxSpd가 더 높아질 수 있는 인접노드 가져오기
        for (int i=0; i<adjs.size(); i++) { // 그래프를 대각선 방향으로 탐색
            idx adj = adjs[i];
            if (G.getMaxPath(now) < G.getLimit(adj)) // 만약 인접노드의 제한속도가 현재노드보다 크다면
                G.compare_set_MaxPath(adj, G.getMaxPath(now));
            else // 인접노드의 제한속도가 현재노드보다 같거나 작다면
                G.compare_set_MaxPath(adj, G.getLimit(adj));
            if (!G.isPushed(adj)) { // 한 번도 큐에 들어간 적이 없는 인접노드라면 큐에 넣기
                Q.push (adj);
                G.checkPush (adj);
            }
        }
    }
    return G.getMaxPath(rows-1, cols-1);
}

int main (int argc, char* argv[]) {
    int t;
    scanf ("%d", &t);
    vector<speed> results(t);
    for (int CASE=0; CASE<t; CASE++) {
        int N, M; // 2 <= N M <= 1000
        scanf ("%d %d", &N, &M);
        Graph G (N, M);
        for (int i=0; i<N; i++) {
            for (int j=0; j<M; j++) {
                speed inp;
                scanf ("%lld", &inp);
                G.assign (i, j, inp);
            }
        }
        results[CASE] = getResult(G);
    }
    for (int CASE=0; CASE<t; CASE++)
        printf ("%lld\n", results[CASE]);
    return 0;
}