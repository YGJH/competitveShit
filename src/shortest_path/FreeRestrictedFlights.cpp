#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;
 
typedef long long ll;
const ll INF = 1e18/2;
 
// 定義邊結構
struct Edge {
    int to, cost;
};
 
// 狀態：目前在節點 node，已使用免費次數 used，累積費用 cost
struct State {
    ll cost;
    int node, used;
    bool operator>(const State &other) const {
        return cost > other.cost;
    }
};
 
// 多維狀態 Dijkstra
// dp[u][j] 表示從 start 出發，到 u 恰好使用 j 次免費航班時的最小費用。
// 參數 K 表示上限（取 K = min(k, n-1)）。
void multiDijkstra(int start, const vector<vector<Edge>> &graph, int n, int K , vector<vector<ll>> &ret) {
    // vector<vector<ll>> dp(n, vector<ll>(K+1, INF));
    ret.assign(n , vector<ll>(K+1 , INF));
    ret[start][0] = 0;
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push({0, start, 0});
    
    while (!pq.empty()){
        State cur = pq.top();
        pq.pop();
        if(cur.cost != ret[cur.node][cur.used]) continue;
        for(const Edge &edge : graph[cur.node]){
            int nxt = edge.to;
            int w = edge.cost;
            // 使用免費航班：費用不增加，但免費次數加 1（前提是還有剩餘）
            if(cur.used < K && ret[nxt][cur.used+1] > cur.cost){
                ret[nxt][cur.used+1] = cur.cost;
                pq.push({cur.cost, nxt, cur.used+1});
            }
            // 付費搭乘：免費次數不變，但費用增加 w
            if(ret[nxt][cur.used] > cur.cost + w){
                ret[nxt][cur.used] = cur.cost + w;
                pq.push({cur.cost + w, nxt, cur.used});
            }
        }
    }
    return ;
}
 
// 計算累積最小值：best[u][j] = min { dp[u][0], dp[u][1], ..., dp[u][j] } 
// 這樣可以方便查詢「在不超過 j 次免費使用下」的最佳花費。
void computeBest(const vector<vector<ll>> &dp, int n, int K , vector<vector<ll>> &ret) {
    ret = dp;
    for (int u = 0; u < n; u++){
        for (int j = 1; j <= K; j++){
            ret[u][j] = min(ret[u][j], ret[u][j-1]);
        }
    }
    return ;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    int a, b;
    ll k_input;
    cin >> a >> b >> k_input;
    // 一條簡單路徑最多經過 n-1 條邊，所以免費次數上限取 min(k, n-1)
    int K = k_input;
    // 建立正向圖與反向圖（反向圖用於計算「從任一點返回家鄉」的花費）
    vector<vector<Edge>> graph(n), rev_graph(n);
    for (int i = 0; i < m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        rev_graph[v].push_back({u, w});
    }
    
    // 分別計算四組 dp：
    // 1. dpA_out：Alice 從家 a 出發到各國的去程狀態
    // 2. dpB_out：Bob 從家 b 出發到各國的去程狀態
    // 3. dpA_in：利用反向圖計算，表示從各國返回 Alice 家 a 的狀態
    // 4. dpB_in：利用反向圖計算，表示從各國返回 Bob 家 b 的狀態
    vector<vector<ll>> dpA_out , dpB_out , dpA_in , dpB_in , bestA_out , bestB_out , bestA_in , bestB_in;
    multiDijkstra(a, graph, n, K , dpA_in);
    multiDijkstra(b, graph, n, K , dpB_in);
    multiDijkstra(a, rev_graph, n, K , dpA_out); // 表示「從 x 到 a」的花費
    multiDijkstra(b, rev_graph, n, K , dpB_out); // 表示「從 x 到 b」的花費
    
    // 轉換成累積最小值版本，方便查詢「在不超過免費次數」下的最佳結果
    computeBest(dpA_out, n, K , bestA_out);
    computeBest(dpB_out, n, K , bestB_out);
    computeBest(dpA_in,  n, K , bestA_in);
    computeBest(dpB_in,  n, K , bestB_in);
    
    ll ans = INF;
    int ans_node = -1;
    // 遍歷所有候選會面國家（排除 Alice 與 Bob 的家鄉）
    for (int x = 0; x < n; x++){
        if (x == a || x == b) continue;
        ll costA = INF;
        // 對於 Alice，枚舉去程使用 j 次免費航班，則回程最多可以使用 K - j 次
        for (int j = 0; j <= K; j++){
            int rem = K - j;
            if (bestA_out[x][j] < INF && bestA_in[x][rem] < INF)
                costA = min(costA, bestA_out[x][j] + bestA_in[x][rem]);
        }
        ll costB = INF;
        for (int j = 0; j <= K; j++){
            int rem = K - j;
            if (bestB_out[x][j] < INF && bestB_in[x][rem] < INF)
                costB = min(costB, bestB_out[x][j] + bestB_in[x][rem]);
        }
        if (costA >= INF || costB >= INF) continue;
        ll total = costA + costB;
        // 若總花費更小；若相等則選擇編號較小的國家
        if (total < ans){
            ans = total;
            ans_node = x;
        }
    }
    if (ans_node == -1 || ans_node >= n)
        cout << ">:(";
    else
        cout << ans_node << " " << ans;
    cout << "\n";
    return 0;
}
