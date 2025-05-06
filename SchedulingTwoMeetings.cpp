//https://codeforces.com/gym/105633/problem/K
#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

struct Cand {
    int idx;    // 會議時段編號（1-indexed）
    int pop;    // 出席人數 (即遮罩中 Y 的個數)
    int mask;   // 出席狀態遮罩
    Cand(int i = -1, int p = -1, int m = 0) : idx(i), pop(p), mask(m) {}
};

// inline 函式比較兩個 candidate，優先 pop 數較大；若相等則 idx 較小優先
inline bool better(const Cand &a, const Cand &b) {
    if(a.idx == -1) return false;
    if(b.idx == -1) return true;
    if(a.pop != b.pop) return a.pop > b.pop;
    return a.idx < b.idx;
}

// 內聯合併函式，合併兩組候選 pair（每組存著最多兩筆），返回合併後最好的兩筆資料
inline pair<Cand, Cand> mergePair(const pair<Cand, Cand> &a, const pair<Cand, Cand> &b) {
    // 先將所有候選放入固定陣列中
    Cand cands[4];
    int cnt = 0;
    if(a.first.idx != -1) { cands[cnt++] = a.first; }
    if(a.second.idx != -1) { cands[cnt++] = a.second; }
    if(b.first.idx != -1) { cands[cnt++] = b.first; }
    if(b.second.idx != -1) { cands[cnt++] = b.second; }
    
    // 選出最佳與次佳 (注意要確保不重複同一時段)
    Cand bestCand(-1, -1, 0), secondCand(-1, -1, 0);
    for (int i = 0; i < cnt; i++) {
        if (better(cands[i], bestCand)) {
            secondCand = bestCand;
            bestCand = cands[i];
        } else if (cands[i].idx != bestCand.idx && better(cands[i], secondCand)) {
            secondCand = cands[i];
        }
    }
    return {bestCand, secondCand};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int full = (1 << m) - 1;
    vector<int> masks(n);
    vector<int> pop(n);
    vector<string> schedule(n);
    for (int i = 0; i < n; i++){
        cin >> schedule[i];
        int mask = 0;
        for (int j = 0; j < m; j++){
            if(schedule[i][j] == 'Y'){
                mask |= (1 << j);
            }
        }
        masks[i] = mask;
        pop[i] = __builtin_popcount(mask);
    }

    // dp 陣列大小為 2^m，每個 dp[mask] 存一對 candidate (最佳, 次佳)
    int size = (1 << m);
    vector< pair<Cand, Cand> > dp(size, {Cand(), Cand()});
    for (int i = 0; i < size; i++){
        dp[i] = {Cand(), Cand()};
    }
    vector<bool> used(size, false);
    vector<int> occur; // 記錄實際出現過的遮罩值
    // 將每個候選時段加入到 dp[其遮罩] 中
    for (int i = 0; i < n; i++){
        int b = masks[i];
        Cand c(i+1, pop[i], b);
        // 更新 dp[b] 的候選對 (內部只有兩筆)
        if(dp[b].first.idx == -1 || better(c, dp[b].first)){
            dp[b].second = dp[b].first;
            dp[b].first = c;
        } else if(dp[b].second.idx == -1 || (c.idx != dp[b].first.idx && better(c, dp[b].second))){
            dp[b].second = c;
        }
        if (!used[b]) {
            used[b] = true;
            occur.push_back(b);
        }
    }

    // SOS DP 部分：對所有 mask 進行狀態傳遞，不需要用 vector 動態配置
    for (int bit = 0; bit < m; bit++){
        for (int mask = 0; mask < size; mask++){
            if(!(mask & (1 << bit))){
                int nm = mask | (1 << bit);
                dp[mask] = mergePair(dp[mask], dp[nm]);
            }
        }
    }

    // 根據題目要求，我們要找兩個候選時段 (i, j)，滿足：
    // 1. mask[i] | mask[j] == full  (即每位評審至少現場一次)
    // 2. 最大化共同行現 (事實上也等價於 pop[i] + pop[j] 最大)
    // 3. 如分數 tie，則選第一時段編號較小，再第二時段較小。
    int bestScore = -1;
    pair<int,int> bestPair = {INT_MAX, INT_MAX};
    bool found = false;
    // 遍歷每個候選時段作為第一場 (必須較早，i+1 為時段編號)
    for (int i = 0; i < n; i++){
        int A = masks[i];
        int missing = full & ~A; // i 的遮罩中缺失的位
        // 從 dp[missing] 中查詢最佳 candidate，注意如果 dp[missing].first 就是同一個 (i+1)，則選用第二優解
        Cand candidateJ;
        if(dp[missing].first.idx == i+1) {
            candidateJ = dp[missing].second;
        } else {
            candidateJ = dp[missing].first;
        }
        // 必須 candidateJ 有效，且其時段編號必須大於 i+1 (保證第一會議比第二早)
        if(candidateJ.idx == -1 || candidateJ.idx <= i+1) continue;
        int score = pop[i] + candidateJ.pop;
        pair<int,int> currPair = {i+1, candidateJ.idx};
        if(score > bestScore) {
            bestScore = score;
            bestPair = currPair;
            found = true;
        } else if(score == bestScore && currPair < bestPair) {
            bestPair = currPair;
        }
    }
    
    if(!found)
        cout << "No\n";
    else
        cout << bestPair.first << " " << bestPair.second << "\n";
        
    return 0;
}
