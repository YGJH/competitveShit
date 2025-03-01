#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-bmi -bmi2 -popcnt -abm -lzcnt -tbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm")
#pragma G++ optimize(3)
#pragma G++ optimize("Ofast")
#pragma G++ optimize("inline")
#pragma G++ optimize("-bmi -bmi2 -popcnt -abm -lzcnt -tbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm -mmmx -msse -msse2 -msse3 -mssse3 -msse4.1 -msse4.2 -mavx -mavx2 -mfma -mbmi -mbmi2 -mpopcnt -mabm -mlzcnt -mtbm")
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>
using namespace std;
#define int long long

template<class T>
class BIT2D {
private:
    vector<vector<T>> bit;
    int szX = 0, szY = 0;
public:
    BIT2D(int x, int y) {
        bit = vector<vector<T>>(x + 2, vector<T>(y + 2, 0));
        szX = x + 2;
        szY = y + 2;
    }
    inline int lowbit(int n) {
        return (n & (-n));
    }
    void update(int posX, int posY, int val) {
        
        for (; posX < szX; posX += lowbit(posX))
            for (; posY < szY; posY += lowbit(posY)) {
                bit[posX][posY] += val - posX;
            }
    }
    T query(int posX , int posY) {
        auto ret = 0;
        for (; posX ; posX ^= lowbit(posX))
            for (; posY ; posY ^= lowbit(posY)) {
                ret += bit[posX][posY];
            }
        return ret;
    }
};
template<class T>
class BIT {
private:
    vector<T> bit;
    int sz = 0;
public:
    BIT(int sz_) {
        bit = vector<T>(sz_ + 2 ,0);
        sz = sz_ + 2;
    }
    inline int lowbit(int n) {
        return (n & (-n));
    }
    void update(int pos, int val) {
        for (; pos < sz ; pos += lowbit(pos)) {
                bit[pos] += val;
            }
    }
    T query(int pos) {
        T ret = 0;
        for (; pos ; pos ^= lowbit(pos)) {
            ret += bit[pos];
        }
        return ret;
    }
};
bool w = 0; char c;
template<typename T>
inline void re(T& a) {
    w = 0;c = getchar();a = 0; while (c < '0' || c > '9') w |= (c == '-'), c = getchar();
    while (c >= '0' && c <= '9') a = (a << 1) + (a << 3) + (c & 15), c = getchar();
    if (w) a = -a;
    return;
}
char st[30]; int kkkk = 0;
template<typename T>
inline void re(string& input_str, T& a) {
    istringstream iss(input_str);
    iss >> a;
}
template<typename T>
inline void re(char* input_str, T& a) {
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
struct node {
    int x; int v; bool operator<(const node& b) const {
        return x < b.x || (x == b.x && v < b.v);
    }
    bool operator==(const node& a) const {
        return x == a.x && v == a.v;
    }
};

signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    re(n);
    vector<int> X(n);
    vector<int> XX(n); iota(XX.begin() , XX.end() , 0);
    for (auto& x : X) {
        re(x);
    }
    vector<int> V(n);
    vector<int> VV; VV.reserve(n);
    for(auto& v : V) {
        re(v);
        VV.push_back(v);
    }
    sort(V.begin(),V.end());
    V.erase(unique(V.begin() , V.end()), V.end());
    BIT<long long> BB(n+2);
    BIT<long long> BV(n+2);
    sort(XX.begin() , XX.end() , [&]( int a ,  int b) {
        return X[a] < X[b] || (X[a] == X[b] && VV[a] < VV[b]);
    });
    // sort(X.begin() , X.end());
    
    long long sum = 0;
    int tmp = 0;
    for(; tmp < n  ; tmp++) {
        int now = XX[tmp];
        int rank = lower_bound(V.begin() , V.end() , VV[now]) - V.begin() + 1;
        sum += abs(BV.query(rank)*X[now] - BB.query(rank));
        BB.update(rank, X[now]);
        BV.update(rank, 1);
    }
    cout << sum << endl;

    return 0;
}
#ifdef LOCAL
void debug() {}
template<class T> void debug(T var) { cerr << var; }
template<class T, class ...P> void debug(T var, P ...t) { cerr << var << ", "; debug(t...); }
template<class T> void org(T l, T r) { while(l != r) cerr << *l++ << ' '; }
#define de(...) { cerr << "[Line: " << __LINE__ << "][" << #__VA_ARGS__ << "] -> [", debug(__VA_ARGS__), cerr << "]
"; }
#define orange(...) { cerr << "[Line: " << __LINE__ << "][" << #__VA_ARGS__ << "] -> [", org(__VA_ARGS__), cerr << "]
"; }
#else
#define de(...) ((void)0)
#define orange(...) ((void)0)
#endif