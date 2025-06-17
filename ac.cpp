#pragma GCC optimize(1, 2, 3, "Ofast", "inline")
#pragma GCC optimize("O3,unroll-loops")
#pragma G++ optimize(1, 2, 3, "Ofast", "inline")
#pragma G++ optimize("O3,unroll-loops")
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
template <class T> void debug(T var) { cerr << var; }
template <class T, class... P> void debug(T var, P... t) {
	cerr << var << ", ";
	debug(t...);
}
template <class T> void org(T l, T r) {
	while (l != r)
		cerr << *l++ << ' ';
}
#define de(...)                                                                \
	{                                                                          \
		cerr << "[Line: " << __LINE__ << "][" << #__VA_ARGS__ << "] -> [",     \
			debug(__VA_ARGS__), cerr << "]\n";                                 \
	}
#define orange(...)                                                            \
	{                                                                          \
		cerr << "[Line: " << __LINE__ << "][" << #__VA_ARGS__ << "] -> [",     \
			org(__VA_ARGS__), cerr << "]\n";                                   \
	}
#else
#define de(...) ((void)0)
#define orange(...) ((void)0)
#endif

namespace IO {
const i32 msize = 2000000;
char buf[msize], *p1 = buf, *p2 = buf;
char obuf[msize], *p3 = obuf;
#define getc()                                                                 \
	(p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, msize, stdin), p1 == p2)     \
		 ? EOF                                                                 \
		 : *p1++)
#define putac(x)                                                               \
	(p3 - obuf < msize)                                                        \
		? (*p3++ = x)                                                          \
		: (fwrite(obuf, p3 - obuf, 1, stdout), p3 = obuf, *p3++ = x)
template <class T> inline void read(T &x) {
	x = 0;
	i32 f = 1;
	char ch = getc();
	for (; ch < 48 || ch > 57; ch = getc())
		if (ch == '-')
			f = -1;
	for (; ch >= 48 && ch <= 57; ch = getc())
		x = (x << 3) + (x << 1) + (ch ^ 0x30);
	x = x * f;
}
template <class T> void write(const T &x) {
	static i32 c[40];
	if (!x) {
		putac('0');
		return;
	}
	i32 len = 0;
	T k1 = x;
	if (k1 < 0)
		k1 = -k1, putac('-');
	while (k1)
		c[len++] = k1 % 10 ^ 48, k1 /= 10;
	while (len--)
		putac(c[len]);
}
void write(const char *str) {
	while (*str)
		putac(*str++);
}
void write(const string &str) {
	for (char c : str)
		putac(c);
}
void write(const char &c) { putac(c); }
template <typename T, typename... Args> inline void read(T &a, Args &...args) {
	read(a);	   // 讀取第一個變數
	read(args...); // 讀取第一個變數
}
template <typename T, typename... Args>
inline void write(const T &x, const Args &...args) {
	write(x);
	write(args...);
}
inline void flush() { fwrite(obuf, p3 - obuf, 1, stdout); }
} // namespace IO
using IO::read;
using IO::write;
void solve();

signed main() {
	int t = 1;
	while (t--)
		solve();
	IO::flush();
	return 0;
}
vector<int> dp((1 << 20), INF);
vector<int> weight((1 << 20), INF);
void solve() {
	int n, m;
	read(n, m);
	int V[1 + n];
	for (int i = 0; i < n; i++) {
		int tmp;
		read(tmp);
		V[i] = tmp;
	}
	
	dp[0] = 0;
	weight[0] = m;
	for (int i = 1; i < (1 << n); i++) { // i = 1011
		for(int j = 0 ; j < n ; j++) { // j = 1 now = 0011
			if(!(i & (1<<j))) continue;
			int pv = i ^ (1 << j); // pv = 0001
			int a = weight[pv] , b = dp[pv];
			if(a + V[j] > m) a = V[j], b++;
			else a += V[j];
			if(b == dp[i]) { 
				weight[i] = min(a , weight[i]);
				dp[i] = b;
			} else if(b < dp[i]) {
				dp[i] = b;
				weight[i] = a;
			}
		}
	}
	write(dp[(1<<n)-1]);
}