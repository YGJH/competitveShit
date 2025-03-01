#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
private:
    vector<int> tree;
    int size;

public:
    FenwickTree(int n) {
        size = n;
        tree.assign(n + 1, 0);
    }

    void update(int index, int delta) {
        while (index <= size) {
            tree[index] += delta;
            index += index & -index;
        }
    }

    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }

    int query_range(int left, int right) {
        return query(right) - query(left - 1);
    }
};

int count_K_multiple_inversions(int N, long long K, vector<long long>& arr) {
    // Step 1: 離散化 (座標壓縮)
    vector<long long> sorted_values(arr.begin(), arr.end());
    for (long long x : arr) {
        sorted_values.push_back(K * x);
    }
    sort(sorted_values.begin(), sorted_values.end());
    sorted_values.erase(unique(sorted_values.begin(), sorted_values.end()), sorted_values.end());

    // 建立 rank 編號
    // unordered_map<long long, int> rank;
    vector<int> rank = sorted_values;
    for (int i = 0; i < sorted_values.size(); ++i) {
        // rank[sorted_values[i]] = i + 1;
        rank[i] = lower_bound(sorted_values.begin() , sorted_values.end() , rand[i]) - sorted_values.begin() + 1;
    }

    // Step 2: 使用 Fenwick Tree 計算 K-multiple 逆序對
    FenwickTree fenwick(sorted_values.size());
    int count = 0;

    for (int i = 0; i < N; ++i) {
        // 計算有多少數比 K * a[i] 大
        int threshold_rank = rank[K * arr[i]];
        count += fenwick.query(sorted_values.size()) - fenwick.query(threshold_rank);

        // 將當前數 a[i] 更新到 Fenwick Tree
        fenwick.update(rank[arr[i]], 1);
    }

    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    long long K;
    cin >> N >> K;
    vector<long long> arr(N);
    for (int i = 0; i < N; ++i) {
        cin >> arr[i];
    }

    cout << count_K_multiple_inversions(N, K, arr) << "\n";
    return 0;
}
