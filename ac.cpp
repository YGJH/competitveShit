#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
// Use 64-bit integer type for counts and answer.
using ll = long long;
 
// Fenwick Tree (BIT) for point updates and prefix sum queries.
struct BIT {
    vector<ll> tree;
    int n;
    BIT(int n) : n(n), tree(n+1, 0) { }
    
    // Increase the value at index idx by delta.
    void update(int idx, ll delta) {
        for(; idx <= n; idx += idx & -idx)
            tree[idx] += delta;
    }
    
    // Query the prefix sum from 1 to idx.
    ll query(int idx) {
        ll res = 0;
        for(; idx > 0; idx -= idx & -idx)
            res += tree[idx];
        return res;
    }
};
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    
    // Since all powers are distinct but can be up to 1e9,
    // we perform coordinate compression.
    vector<int> comp = a;
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    
    // Replace each a[i] with its compressed value (1-indexed).
    for (int i = 0; i < n; i++){
        a[i] = lower_bound(comp.begin(), comp.end(), a[i]) - comp.begin() + 1;
    }
    
    int m = comp.size();
    
    // Compute L: For each j, count how many i < j have a[i] > a[j].
    vector<ll> L(n, 0);
    BIT bitL(m);
    for (int j = 0; j < n; j++){
        // Query the number of elements seen so far that are greater than a[j].
        // That is: total count so far minus count up to a[j].
        L[j] = bitL.query(m) - bitL.query(a[j]);
        bitL.update(a[j], 1);
    }
    
    // Compute R: For each j, count how many k > j have a[k] < a[j].
    vector<ll> R(n, 0);
    BIT bitR(m);
    for (int j = n - 1; j >= 0; j--){
        // Query the number of elements to the right that are less than a[j].
        R[j] = bitR.query(a[j] - 1);
        bitR.update(a[j], 1);
    }
    
    // Sum over j: L[j] * R[j]
    ll answer = 0;
    for (int j = 0; j < n; j++){
        answer += L[j] * R[j];
    }
    
    cout << answer << "\n";
    return 0;
}
