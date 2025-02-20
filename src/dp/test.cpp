#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 比較兩個索引序列的字典序，較小者代表所選活動在原輸入中較早出現
bool lexCompare(const vector<int>& a, const vector<int>& b) {
    int n = min(a.size(), b.size());
    for (int i = 0; i < n; i++){
        if(a[i] < b[i]) return true;
        else if(a[i] > b[i]) return false;
    }
    return a.size() < b.size();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while(true) {
        int T;
        if (!(cin >> T)) break;
        if(T == 0) break;  // 終止條件

        int N;
        cin >> N;
        vector<int> arr(N);
        for (int i = 0; i < N; i++){
            cin >> arr[i];
        }

        // dp[s] 儲存「達到總和 s」時所選活動（以原始索引表示）的最佳序列
        // reachable[s] 表示總和 s 是否可以達到
        vector<vector<int>> dp(T+1);
        vector<bool> reachable(T+1, false);
        reachable[0] = true;
        dp[0] = vector<int>(); // 空集合達到 0
        int bestSum = 0;
        // 典型的 0/1 背包（從前到後遍歷每個活動，但內部反向更新）
        for (int i = 0; i < N; i++){
            int value = arr[i];
            for (int s = T; s >= value; s--){
                if(reachable[s - value]){
                    // 建立候選解：來自 dp[s-value] 加上本活動 i
                    vector<int> candidate = dp[s - value];
                    candidate.push_back(i);
                    // 如果 s 尚未達成，或候選解的「原始索引序列」字典序更小，則更新 dp[s]
                    if(!reac    hable[s] || lexCompare(candidate, dp[s])){
                        dp[s] = candidate;
                        reachable[s] = true;
                        bestSum = max(bestSum , s);
                    }
                }
            }
        }

        // cout << "dp: \n";
        // for(int i = 1 ; i <= T ; i++) {
        //     cout << "layer " << i << " : ";
        //     if(!reachable[i]) {
        //         cout << "unreachable" << endl;
        //         continue;
        //     }
        //     for(int j = 0 ; j < dp[i].size() ; j++) {
        //         cout << dp[i][j] << ' ';
        //     }
        //     cout << endl;
        // }

        // 從 T 往下找第一個可以達到的總和
        // int bestSum = 0;
        // for (int s = T; s >= 0; s--){
        //     if(reachable[s]){
        //         bestSum = s;
        //         break;
        //     }
        // }
        // dp[bestSum] 即為最佳解所選活動的索引序列（原始順序自然遞增）
        // 輸出時依照原始順序輸出對應的活動時長，最後再輸出總和
        for (int idx : dp[bestSum]) {
            cout << arr[idx] << " ";
        }
        cout << bestSum << "\n";
    }
    return 0;
}
