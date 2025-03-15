#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct State {
    int remainder;   // 當前數字 mod K
    int digitSum;    // 累積的數字和
    // 比較運算子，讓 priority_queue 以最小的 digitSum 優先
    bool operator>(const State &other) const {
        return digitSum > other.digitSum;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;
    
    // 初始化每個餘數狀態的最小累積數字和為無窮大
    const int INF = numeric_limits<int>::max();
    vector<int> minSum(K, INF);

    // 使用 priority_queue (小根堆) 進行 Dijkstra 搜索
    priority_queue<State, vector<State>, greater<State>> pq;

    // 對於首位數字，不能是 0，因此從 1 到 9 初始化
    for (int d = 1; d <= 9; d++) {
        int r = d % K;
        if (d < minSum[r]) {
            minSum[r] = d;
            pq.push({r, d});
        }
    }
    
    while(!pq.empty()){
        auto cur = pq.top();
        pq.pop();
        
        // 若此狀態的累積數字和已大於記錄值則跳過
        if (cur.digitSum > minSum[cur.remainder]) continue;
        
        // 找到餘數為 0 的數字，輸出其數字和後結束
        if(cur.remainder == 0){
            cout << cur.digitSum << "\n";
            return 0;
        }
        
        // 從當前狀態嘗試添加數字 0 ~ 9
        for (int d = 0; d <= 9; d++) {
            int newRemainder = (cur.remainder * 10 + d) % K;
            int newSum = cur.digitSum + d;
            if (newSum < minSum[newRemainder]) {
                minSum[newRemainder] = newSum;
                pq.push({newRemainder, newSum});
            }
        }
    }
    
    // 理論上不應走到這裡，因為一定有解
    return 0;
}
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct State {
    int remainder;   // 當前數字 mod K
    int digitSum;    // 累積的數字和
    // 比較運算子，讓 priority_queue 以最小的 digitSum 優先
    bool operator>(const State &other) const {
        return digitSum > other.digitSum;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;
    
    // 初始化每個餘數狀態的最小累積數字和為無窮大
    const int INF = numeric_limits<int>::max();
    vector<int> minSum(K, INF);

    // 使用 priority_queue (小根堆) 進行 Dijkstra 搜索
    priority_queue<State, vector<State>, greater<State>> pq;
    
    // 對於首位數字，不能是 0，因此從 1 到 9 初始化
    for (int d = 1; d <= 9; d++) {
        int r = d % K;
        if (d < minSum[r]) {
            minSum[r] = d;
            pq.push({r, d});
        }
    }
    
    while(!pq.empty()){
        auto cur = pq.top();
        pq.pop();
        
        // 若此狀態的累積數字和已大於記錄值則跳過
        if (cur.digitSum > minSum[cur.remainder]) continue;
        
        // 找到餘數為 0 的數字，輸出其數字和後結束
        if(cur.remainder == 0){
            cout << cur.digitSum << "\n";
            return 0;
        }
        
        // 從當前狀態嘗試添加數字 0 ~ 9
        for (int d = 0; d <= 9; d++) {
            int newRemainder = (cur.remainder * 10 + d) % K;
            int newSum = cur.digitSum + d;
            if (newSum < minSum[newRemainder]) {
                minSum[newRemainder] = newSum;
                pq.push({newRemainder, newSum});
            }
        }
    }
    
    // 理論上不應走到這裡，因為一定有解
    return 0;
}
