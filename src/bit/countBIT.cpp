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


struct fenwick {
    static const int N = 1e6+3;
    int bit[N];
    void init() {
        memset(bit , 0 , sizeof(bit));
        return ;
    }
    void update(int n , int v) {
        n+=2;
        for( ; n < N ; n+=(n&-n)){
            bit[n] += v;
        }
        return ;
    }
    int qry(int n) {
        n+=2;
        int ret=0;
        for(; n  ; n -= (n&-n)) {
            ret += bit[n];
        }
        return ret;
    }
};
signed main() {

    fenwick BT , B;
    int n;
    re(n);
    B.init();
    vector<int> arr(n);
    for(auto &a : arr) {
        re(a);
    }
    auto tp = arr;
    #define all(x) (x).begin(),(x).end()
    sort(all(tp));
    tp.erase(unique(all(tp)) , tp.end());
    for(auto &a : arr) {
        a = lower_bound(all(tp) , a) - tp.begin() + 1;
    }
    vector<int> l , r(n); l.reserve(n+3);
    
    for(auto &a : arr) {
        l.push_back(B.qry(a)-B.qry(a-1));
        B.update(a, 1);
    }
    B.init();
    for(int i = arr.size() - 1 ; i >= 0  ; i--) {
        r[i] = (B.qry(arr[i])-B.qry(arr[i]-1));
        B.update(arr[i], 1);
    }
    // cerr << "l: ";
    // for(auto i = 0 ; i < arr.size() ; i++) {
    //     cerr << l[i] << ' ';
    // }
    // cerr << endl << "r: ";
    // for(auto i = 0 ; i < arr.size() ; i++) {
    //     cerr << r[i] << ' ';
    // }
    // cerr << endl;
    int ans = 0;
    B.init();
    for (int i = arr.size() - 1 ; i >= 0 ; i--) {
        ans += B.qry(l[i]-1);
        B.update(r[i],1);
    }

    wr(ans);


    return 0;
}