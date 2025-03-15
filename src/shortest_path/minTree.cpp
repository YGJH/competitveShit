#pragma GCC optimize(1,2,3,"Ofast","inline")
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

#define int i64
#define FF first
#define SS second
#define SZ(x) ((i32)(x).size())
#define PB push_back
#define EB emplace_back
#define all(x) (x).begin(), (x).end()
using i128 = __int128_t;
using ui64 = uint64_t;
using i64 = int64_t;
using ui32 = uint32_t;
using i32 = int32_t;
using ld = long double;
using P32 = pair<i32, i32>;
using P64 = pair<i64, i64>;
const i64 INF = 1e18;
const ld eps = 1e-8L;
namespace IO {
    const i32 msize = 200000;
    char buf[msize], *p1 = buf, *p2 = buf;
    char obuf[msize], *p3 = obuf;
    #define getc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, msize, stdin), p1 == p2) ? EOF : *p1++)
    #define putac(x) (p3 - obuf < msize) ? (*p3 ++ = x) :(fwrite(obuf, p3 - obuf, 1, stdout), p3 = obuf, *p3 ++ = x)
    template<class T> inline void read(T &x) {
        x = 0;
        i32 f = 1;
        char ch = getc();
        for (; ch < 48 || ch > 57; ch = getc()) if (ch == '-') f = -1;
        for (; ch >= 48 && ch <= 57; ch = getc()) x = (x << 3) + (x << 1) + (ch ^ 0x30);
        x = x * f;
    }
    template<class T> void write(const T &x) {
        static i32 c[40];
        if (!x) { putac('0'); return; }
        i32 len = 0;
        T k1 = x;
        if (k1 < 0) k1 = -k1, putac('-');
        while (k1) c[len++] = k1 % 10 ^ 48, k1 /= 10;
        while (len--) putac(c[len]);
    }
    void write(const char *str) { while (*str) putac(*str++); }
    void write(const string &str) { for (char c : str) putac(c); }
    void write(const char &c) { putac(c); }
    template<typename T, typename... Args>
    inline void read(T &x, Args&... args) {
        read(x);  // 讀取第一個變數
        read(args...); // 展開剩餘變數的讀取
    }
    template<typename T, typename... Args>
    inline void write(const T &x, const Args&... args) {
        write(x);
        write(args...);
    }
    inline void flush() { fwrite(obuf, p3 - obuf, 1, stdout); }
}
using IO::read;
using IO::write;
bitset<200004> vis;
struct node{
    int w , v, id;
};
struct cmp{ 
    bool operator()(const node &a , const node &b) {
        return a.w > b.w;
    }
};
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
vector<int> ans;
signed main() {
    int n , m;
    int u , v  ,w;
    priority_queue<node , vector<node>, cmp> que;
    read(n, m);
    vector<vector<node>> E(n+3,vector<node>());
    for(auto i = 1 ; i <= m ; i++) {
        read(u , v, w);
        E[u].push_back({w , v, i});
        E[v].push_back({w , u, i});
    }
    que.push({0 , 1 , 0});
    while(!que.empty()) {
        auto now = que.top();
        que.pop();
        if(vis[now.v]) continue;
        vis[now.v] = 1;
        // de(now.w , now.v , now.id);
        ans.push_back(now.id);
        for(auto &e : E[now.v]) {
            if(!vis[e.v]) {
                que.push({now.w + e.w, e.v , e.id});
            }
        }
    }

    for(auto i = 1 ; i < ans.size() ; i++) {
        write(ans[i] , ' ');
    }

    IO::flush();

    return 0;
}