#include <bits/stdc++.h>
using namespace std;

#define piyan puts("操我屁眼");
#define fk puts("幹你娘幹你娘");
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

struct xin{
	
}
using IO::read;
using IO::write;

struct MinCostMaxFlow{
typedef int Tcost;
  static const int MAXV = 20010;
  static const int INFf = 1000000;
  static const Tcost INFc  = 1e9;
  struct Edge{
    int v, cap;
    Tcost w;
    int rev;
    Edge(){}
    Edge(int t2, int t3, Tcost t4, int t5)
    : v(t2), cap(t3), w(t4), rev(t5) {}
  };
  int V, s, t;
  vector<Edge> g[MAXV];
  void init(int n, int _s, int _t){
    V = n; s = _s; t = _t;
    for(int i = 0; i <= V; i++) g[i].clear();
  }
  void addEdge(int a, int b, int cap, Tcost w){
    g[a].push_back(Edge(b, cap, w, (int)g[b].size()));
    g[b].push_back(Edge(a, 0, -w, (int)g[a].size()-1));
  }
  Tcost d[MAXV];
  int id[MAXV], mom[MAXV];
  bool inqu[MAXV];
  queue<int> q;
  pair<int,Tcost> solve(){
    int mxf = 0; Tcost mnc = 0;
    while(1){
      fill(d, d+1+V, INFc);
      fill(inqu, inqu+1+V, 0);
      fill(mom, mom+1+V, -1);
      mom[s] = s;
      d[s] = 0;
      q.push(s); inqu[s] = 1;
      while(q.size()){
        int u = q.front(); q.pop();
        inqu[u] = 0;
        for(int i = 0; i < (int) g[u].size(); i++){
          Edge &e = g[u][i];
          int v = e.v;
          if(e.cap > 0 && d[v] > d[u]+e.w){
            d[v] = d[u]+e.w;
            mom[v] = u;
            id[v] = i;
            if(!inqu[v]) q.push(v), inqu[v] = 1;
      } } }
      if(mom[t] == -1) break ;
      int df = INFf;
      for(int u = t; u != s; u = mom[u])
        df = min(df, g[mom[u]][id[u]].cap);
      for(int u = t; u != s; u = mom[u]){
        Edge &e = g[mom[u]][id[u]];
        e.cap             -= df;
        g[e.v][e.rev].cap += df;
      }
      mxf += df;
      mnc += df*d[t];
    }
    return {mxf,mnc};
} }flow;

signed main() {
	i32 n , k;
	xin >> n >> k;
	MinCostMaxFlow solver;
	const i32 source = 0;
	const i32 target = 50 + 2; 
	solver.init(50 + 3 , source , target)
	const i64 INF_2 = INF / 2;
	vector<vector<i32>> v(n , vector<i32>(n));
	for(i32 i = 0 ; i < n ; i++) {
		for(i32 j = 0 ; j < n ; j++) {
			xin >> v[i][j];
			switch(i) {
				case (i < n - 1):
				{
					solver.addEdge(i*n + j , (i + 1) * n + j , 1 , v[i][j]);
					solver.addEdge(i*n + j , (i+1) * n + j , INF , 0);
					switch (j)
					{
						case (j < n - 1):
						{
							solver.addEdge(i*n + j , i * n + j + 1 , 1 , v[i][j]);
							solver.addEdge(i*n + j , i * n + j + 1 , INF , 0);
							break;
						}
					}
					break;
				}
				default: {
					if(j < n - 1) {
						solver.addEdge(i*n + j , i * n + j + 1 , 1 , v[i][j]);
						solver.addEdge(i*n + j , i * n + j + 1 , INF , 0);
					}
				}
			}

		}
	}


	const i64 ans = solver.solve();
	xout << ans << endl;

	IO::flush();

	return 0;
}
