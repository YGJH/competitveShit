#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-bmi -bmi2 -popcnt -abm -lzcnt -tbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm")
#pragma G++ optimize(3)
#pragma G++ optimize("Ofast")
#pragma G++ optimize("inline")
#pragma G++ optimize("-bmi -bmi2 -popcnt -abm -lzcnt -tbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm")
#pragma G++ optimize("-fconstexpr-loop-limit=")
#include <bits/stdc++.h>
using namespace std;

#define int long long

bool w = 0; char c;
template<typename T>
inline void re(T& a) {
    w=0;c = getchar();a = 0; while ((c < '0' || c > '9') && c != EOF) w |= (c == '-'), c = getchar();
    while (c >= '0' && c <= '9') a = (a << 1) + (a << 3) + (c & 15), c = getchar();
    if (w) a = -a;
    return;
}
char st[30]; int kkkk = 0;
template<typename T>
inline void re(string&input_str, T& a) {
istringstream iss(input_str);
iss >> a;
}
template<typename T>
inline void re(char *input_str, T& a) {
istringstream iss(input_str);
iss >> a;
    return;
}
template<typename T>
inline void wr(T a) {
kkkk = 0;
    if (a == 0) { putchar('0'); return; }
    if (a < 0)putchar('-'), a = -a;
    while (a) { st[kkkk++] = a % 10 + '0', a /= 10; }
    while (kkkk) { putchar(st[--kkkk]); }
    return;
}
struct BIT{
    vector<int> bit;
    int sz;
    BIT(int n) :
    sz(n+2),
    bit(n+3 ,0){};
    int lowbit(int n) {
        return n&-n;
    }
    void update(int s , int v) {
        for(; s < sz ; s += lowbit(s)) {
            bit[s] += v;
        }
    }
    int query(int n) {
        int ret = 0 ;
        while(n) {
            ret += bit[n];
            n ^= lowbit(n);
        }
        return ret;
    }
};
#define LOCAL
#ifdef LOCAL
void debug() {}
template<class T> void debug(T var) { cerr << var; }
template<class T, class ...P> void debug(T var, P ...t) { cerr << var << ", "; debug(t...); }
template<class T> void org(T l, T r) { while(l != r) cerr << *l++ << ' '; }
#define de(...) { cerr << "[Line: " << __LINE__ << "][" << #__VA_ARGS__ << "] -> [", debug(__VA_ARGS__), cerr << "]\n"; }
#define orange(...) { cerr << "[Line: " << __LINE__ << "][" << #__VA_ARGS__ << "] -> [", org(__VA_ARGS__), cerr << "]\n"; }
#else
#define de(...) ((void)0)
#define orange(...) ((void)0)
#endif
constexpr int N = 1000000;
constexpr int MOD = 1000000007;

constexpr std::array<long long, N + 1> compute_factorials() {
    std::array<long long, N + 1> fac = {};
    fac[0] = 1;
    for (int i = 1; i <= N; ++i) {
        fac[i] = (fac[i - 1] * i) ;//% MOD;
    }
    return fac;
}


signed main() {
    int n; re(n);
    // auto factorials = compute_factorials();
    // std::vector<long long> fac_vector(factorials.begin(), factorials.end());

    vector<int> V(n);
    for(auto &v : V) re(v);
    BIT B(n);
    BIT B2(n);
    auto temp = V;
    #define all(x) (x).begin(),(x).end()
    sort(all(temp));
    temp.erase(unique(all(temp)) , temp.end());
    for(auto &a : V) {
        a = lower_bound(all(temp) , a) - temp.begin() + 1;
    }
    // org(all(V));
    int ans = 0, tmp = 0;
    vector<int> R;R.resize(n+2);
    for(auto i = n - 1 ; i >= 0 ; i--) {
        R[i] = (B.query(V[i]-1));
        B.update(V[i], 1);
    }
    
    for(auto i = 0 ; i < n ; i++) {
        // de(tmp-B2.query(V[i]));
        // de(R[i]);
        // de(i);
        ans += R[i] * (tmp - B2.query(V[i]));
        B2.update(V[i], 1);
        tmp++;
    }
    wr(ans);
    

    return 0;
}