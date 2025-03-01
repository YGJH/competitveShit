#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-bmi -bmi2 -popcnt -abm -lzcnt -tbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm")
#pragma G++ optimize(3)
#pragma G++ optimize("Ofast")
#pragma G++ optimize("inline")
#pragma G++ optimize("-bmi -bmi2 -popcnt -abm -lzcnt -tbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm")
#include <bits/stdc++.h>
using namespace std;
struct node{
	int w , v;
};
node W[102];
uint64_t dp[(int)1e6+2];
int i = 0  ;
signed main() {
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n , w;
	cin >> n >> w;
	for(i = 1 ; i <= n ; i++) {
		cin >> W[i].w >> W[i].v;
	}
	for(i = 1 ; i <= n ; i++) {
		for(int j = w ; j >= W[i].w ; j--) {
			if(j - W[i].w >= 0) {
				dp[j] = max(dp[j], dp[j - W[i].w] + W[i].v);
			}
		}
	}
	cout << dp[w] << endl;

}