#include <iostream>
#include <vector>
using namespace std;
 
typedef long long ll;
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        ll k;
        cin >> n >> k;
        
        vector<ll> a(n), b(n);
        ll sumA = 0, sumB = 0;
        for (int i = 0; i < n; i++){
            cin >> a[i];
            sumA += a[i];
        }
        for (int i = 0; i < n; i++){
            cin >> b[i];
            sumB += b[i];
        }
        
        // 上界可以用 (sumB + k) / sumA 為一個粗略的上限
        ll lo = 0, hi = (sumB + k) / sumA;
        
        while(lo < hi){
            ll mid = (lo + hi + 1) / 2;  // 取上中位數
            ll extraNeeded = 0;
            
            // 檢查是否可以完成 mid 份表單
            for (int i = 0; i < n; i++){
                ll required = mid * a[i];
                if(required > b[i]){
                    extraNeeded += (required - b[i]);
                    if(extraNeeded > k) break;  // 早停：已超過特殊簽名數量
                }
            }
            
            if(extraNeeded <= k)
                lo = mid;   // mid 可行，嘗試更大的數
            else
                hi = mid - 1;  // mid 不可行，降低上界
        }
        
        cout << lo << "\n";
    }
    
    return 0;
}
