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

#define int long long
#define all(x) (x).begin(),(x).end()


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
    static const int N = 500000+3;
    void init() {
        bit = vector<int>(N);
    }
    void update(int pos , int val) {
        pos+=2;
        for(; pos < N ; pos += pos&-pos) {
            bit[pos] += val;
        }
        return ;
    }
    int qry(int pos) {
        pos+=2;
        int ret = 0;
        for(; pos ; pos -= pos&-pos) {
            ret += bit[pos];
        }
        return ret;
    }
};
// #define LOCAL
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
signed main() {

    int n , m;
    re(n);re(m);
    BIT B, BT , BB;
    B.init();
    BT.init();
    BB.init();
    vector<int> V(n);
    vector<int> diff;diff.reserve(n+3);
    bool flag = 0;
    for(auto &v:V) {
        re(v);
        diff.push_back(m-v);
        if(m-v == 0) flag = 1;
    }
    auto tmp = V;
    sort(all(tmp));
    tmp.erase(unique(all(tmp)) , tmp.end());
    vector<int> cnt(1e6+3 , 0);
    for(int i = 0 ; i < V.size() ; i++) {
        V[i] = lower_bound(all(tmp) , V[i]) - tmp.begin() + 1;
        B.update(V[i], diff[i]);
        BT.update(V[i], 1);
    }
    int ans = 0;
    for(int i = 0 ; i < V.size() ; i++) {
        // auto C = BT.qry(V[i]);
        // de(B.qry(V[i]-1));

        auto A = B.qry(V[i]-1) - (BT.qry(V[i]-1) * diff[i]) + (cnt[V[i]]) + BB.qry(V[i]-1);
        BB.update(V[i], 1);
        cnt[V[i]]++;
        if(A >= m - 1) {
            wr(-1);
            putchar('\n');
            continue;
        }
        else {
            wr(A);
            putchar('\n');
            continue;
        }
    }

    return 0;
}