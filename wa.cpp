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
vector<int> sz;
vector<int> fa;

int cnt;
bitset<100001> vis;
vector<int> V;

bitset<100001> tag;

int findd(int n) {
    // de(fa[n]);
    return (n == fa[n])?n:fa[n] = findd(fa[n]);
}
void dfs(int now, int f) {
    if(vis[now]) {
        fa[now] = f;
        sz[now] = cnt;
        return ;
    }
    vis[now] = 1;
    cnt++;;
    dfs(V[now] , now);
    // de(cnt);
    sz[now] = cnt;
    fa[now] = f;
    return ;
}

void solve() {
    int n;
    read(n);
    // de(n);
    vector<int> q(n+1);
    tag.reset();
    fa.resize(n+1);
    iota(all(fa) , 0);
    V.clear();
    V.resize(n + 1);
    vis.reset();
    sz.assign(n+1 ,1);
    for(int i = 1 ; i <= n ; i++) {
        read(V[i]);
    }
    for(int i = 1; i <= n ; i++) {
        if(vis[V[i]] == 0) {
            cnt = 0;
            dfs(V[i] , V[i]);
        }
    }
    int now = 0;
    for(int i = 1 ; i <= n ; i++) {
        read(q[i]);

        auto tmp = findd(q[i]);
        // de(tmp);
        if(tag[tmp] == 0) {
            tag[tmp] = 1;
            now += sz[tmp];
        }
        // de(now);
        write(now ,' ');

    }
    write('\n');
    // orange(all(sz));
    return ;
}

signed main(){
    int t = 1;
    read(t);
    while(t--) {
        solve();
    }

    IO::flush();
    return 0;

}
