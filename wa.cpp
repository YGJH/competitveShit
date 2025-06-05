#include <bits/stdc++.h>
using namespace std;

/*
  題目：無向圖最多只有一個簡單環，若存在，輸出其長度；否則輸出 "There is no cycle."

  思路：
  1. 在讀邊的同時，先檢查「重邊」情形，如果兩個相同端點的邊出現第二次，就直接輸出 2 並結束。
  2. 若無重邊，則建構鄰接串列 adj[]，並執行一次 DFS 找「回邊」，一旦遇到 visited 且不是 parent 的鄰居，就算到一個簡單環，
     計算環長 = depth[cur] - depth[neighbor] + 1。然後設置全域變數 found_cycle_len，停止所有遞迴。
  3. 結束後，若 found_cycle_len != -1 就輸出它，否則輸出 "There is no cycle."
*/

static const int MAXN = 100000 + 5;

int n, m;
vector<int> adj[MAXN];
bool vis[MAXN];
int parent_node[MAXN];
int depth_arr[MAXN];
// -1 代表還沒找到；一旦發現 cycle，設為 cycle 的長度
int found_cycle_len = -1;

// DFS 函式：從節點 u 開始，parent 是 p
void dfs(int u, int p) {
    // 如果已經在別處找到 cycle，就直接跳回
    if (found_cycle_len != -1) return;

    vis[u] = true;
    parent_node[u] = p;

    for (int w : adj[u]) {
        // 如果已經在別處找到了 cycle，就一律回傳
        if (found_cycle_len != -1) return;

        if (!vis[w]) {
            // 還沒拜訪過，就繼續往下
            depth_arr[w] = depth_arr[u] + 1;
            dfs(w, u);
        }
        else if (w != p) {
            // w 已拜訪過，且不是 u 的 parent → 找到「回邊」
            // 環長 = depth[u] - depth[w] + 1
            found_cycle_len = (depth_arr[u] - depth_arr[w]) + 1;
            return;
        }
        // 如果 w == p，就跳過（那是從 p 走到 u 時用的那條邊）
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    // 用來檢查重邊的資料結構：key=(min(u,v)<<32)|max(u,v)
    unordered_set<long long> seenEdges;
    seenEdges.reserve(m * 2);

    vector<pair<int,int>> edges;
    edges.reserve(m);

    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        edges.emplace_back(x, y);

        int a = min(x, y), b = max(x, y);
        long long key = ( (long long)a << 32 ) | (long long)b;
        if (seenEdges.count(key)) {
            // 一旦發現重邊，這個簡單環必定長度為 2
            cout << 2 << "\n";
            return 0;
        }
        seenEdges.insert(key);
    }

    // 如果沒提早 return，代表沒有重邊，要把所有邊加入鄰接串列
    for (auto & e : edges) {
        int u = e.first, v = e.second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 初始化：所有節點都還沒拜訪
    for (int i = 1; i <= n; i++) {
        vis[i] = false;
        parent_node[i] = -1;
        depth_arr[i] = 0;
    }

    // 由於圖保證是連通的，所以只要從 1 開始跑一次 DFS 就行
    depth_arr[1] = 0;
    dfs(1, 0);

    if (found_cycle_len != -1) {
        cout << found_cycle_len << "\n";
    }
    else {
        cout << "There is no cycle.\n";
    }

    return 0;
}
