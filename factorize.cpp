// https://judge.yosupo.jp/problem/factorize
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 可避免 overflow 的模乘，用 __int128 計算
ll mod_mul(ll a, ll b, ll mod) {
    __int128 res = a;
    res *= b;
    res %= mod;
    return (ll)res;
}

// 快速模指數運算：計算 (a^b) % mod
ll mod_pow(ll a, ll b, ll mod) {
    ll result = 1;
    a %= mod;
    while(b > 0) {
        if(b & 1) result = mod_mul(result, a, mod);
        a = mod_mul(a, a, mod);
        b >>= 1;
    }
    return result;
}

// Miller-Rabin 素數測試
bool isPrime(ll n) {
    if(n < 2) return false;
    // 檢查小質數
    int smallPrimes[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (int i = 0; i < 12; i++) {
        if(n == smallPrimes[i]) return true;
        if(n % smallPrimes[i] == 0) return false;
    }
    
    ll d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d /= 2;
        s++;
    }
    // 使用固定的測試基數
    int testPrimes[7] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (int a : testPrimes) {
        if(a % n == 0) continue;
        ll x = mod_pow(a, d, n);
        if(x == 1 || x == n - 1) continue;
        bool cont = false;
        for (int r = 1; r < s; r++) {
            x = mod_mul(x, x, n);
            if(x == n - 1) {
                cont = true;
                break;
            }
        }
        if(!cont) return false;
    }
    return true;
}

// Pollard Rho 算法，尋找 n 的一個非平凡因數
ll pollardRho(ll n) {
    if(n % 2 == 0) return 2;
    ll x = rand() % (n - 2) + 2;
    ll y = x;
    ll c = rand() % (n - 1) + 1;
    ll d = 1;
    while(d == 1) {
        x = (mod_mul(x, x, n) + c) % n;
        y = (mod_mul(y, y, n) + c) % n;
        y = (mod_mul(y, y, n) + c) % n;
        d = gcd(abs(x - y), n);
        if(d == n) return pollardRho(n);
    }
    return d;
}

// 遞迴分解 n，將質因數存入 factors 向量中
void factorize(ll n, vector<ll>& factors) {
    if(n == 1) return;
    if(isPrime(n)) {
        factors.push_back(n);
        return;
    }
    ll factor = pollardRho(n);
    factorize(factor, factors);
    factorize(n / factor, factors);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q;
    cin >> Q;
    while(Q--){
        ll n;
        cin >> n;
        // 特殊處理 n = 1
        if(n == 1) {
            cout << "0" << "\n";
            continue;
        }
        vector<ll> factors;
        factorize(n, factors);
        sort(factors.begin(), factors.end());
        // 輸出格式：第一個數為因數個數，其後依序輸出所有因數
        cout << factors.size();
        for(auto p : factors) {
            cout << " " << p;
        }
        cout << "\n";
    }
    
    return 0;
}
