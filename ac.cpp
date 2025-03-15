#include <bits/stdc++.h>
using namespace std;

// 邊的結構表示法
struct Edge {
    int u, v, w;
};

// 使用 path compression 找到集合代表元素
int findParent(vector<int> &parent, int i) {
    if (parent[i] != i)
        parent[i] = findParent(parent, parent[i]);
    return parent[i];
}

// 使用 union by rank 合併兩個集合
void unionSet(vector<int> &parent, vector<int> &rank, int x, int y) {
    int xroot = findParent(parent, x);
    int yroot = findParent(parent, y);
    if (xroot == yroot)
        return;
    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    } else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    } else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}
#ifdef LOCAL
void debug() {}
template<class T> void debug(T var) { cerr << var; }
template<class T, class ...P> void debug(T var, P ...t) { cerr << var << ", "; debug(t...); }
template<class T> void org(T l, T r) { while(l != r) cerr << *l++ << ' '; }
#define de(...) { cerr << "[Line: " << __LINE__ << "][" << #__VA_ARGS__ << "] -> [", debug(__VA_ARGS__), cerr << "]\n"; }
#define orange(...) { cerr << "[Line: " << __LINE__ << "][" << #__VA_ARGS__ << "] -> [", org(__VA_ARGS__), cerr << "]\n"; }
#else
#define de(...) ((void)0)
#define orange(...) ((void)0)
#endif
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    // assert(N <= 100000 && M <= N + 300);
    vector<Edge> edges(M);
    for (int i = 0; i < M; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    
    // 依照邊的權重由小到大排序
    sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
        return a.w < b.w;
    });

    // 初始化 Union-Find 結構
    vector<int> parent(N), rank(N, 0);
    for (int i = 0; i < N; i++) {
        parent[i] = i;
    }

    int mst_weight = 0;
    // 逐一加入邊，檢查是否會產生 cycle
    for (int i = 0; i < M; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (findParent(parent, u) != findParent(parent, v)) {
            mst_weight += w;
            // de(u , v , w);
            unionSet(parent, rank, u, v);
        }
    }

    cout << "The cost of minimum spanning tree: " << mst_weight << "\n";
    return 0;
}
