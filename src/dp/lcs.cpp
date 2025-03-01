#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-bmi -bmi2 -popcnt -abm -lzcnt -tbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm")
#pragma G++ optimize(3)
#pragma G++ optimize("Ofast")
#pragma G++ optimize("inline")
#pragma G++ optimize("-bmi -bmi2 -popcnt -abm -lzcnt -tbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm")
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;
#define max(a,b) (a>b)?a:b
string str[152];
vector<vector<uint64_t>> dp;
int i , j , t , ans;
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    getline(cin , str[0]);
    t = 1;
    dp.reserve(2000 * 2000);
    while(getline(cin, str[t++]));
    for(int k = 1 ; k < t - 2  ; k+=2) {
        int lena = str[k].length(); 
        int lenb = str[k+1].length();
        dp.assign(lena+1, vector<uint64_t>(lenb+1, 0));
        for(i = 1 ; i <= lena ; i++) {
            for(j = 1 ; j <= lenb ; j++) {
                if(str[k][i-1] == str[k+1][j-1]) {
                    dp[i][j] = dp[i-1][j-1]+1;
                }
                else {
                    dp[i][j] = max(dp[i-1][j] , dp[i][j-1]);
                }
            }
        }
        cout << dp[lena][lenb]  << endl;
    }

    return 0;
}
