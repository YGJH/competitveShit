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
using IO::read;
using IO::write;

struct xout {
    template<typename T>
    xout& operator << (const T &x) {
        IO::write(x);
        return *this;
    }
} xout;
struct xin {
    template<typename T>
    xin& operator >> (T &x) {
        IO::read(x);
        return *this;
    }
} xin;


struct solver{
	i32 n , m;
	i32 *arr;
	i32 ans = 0;
	solver(i32 n , i32 m) {
		this->n = n;
		this->m = m;
		arr = new i32[n+1];
	}
	inline bool check(i32 k) { // return maximum group that could exist
		
		vector<bool> vis(k);
		i32 cnt = k;
		i32 group = 0;
		// vector<int> t;
		for(i32 i = 0 ; i < n ; ++i) {
			if(arr[i] < k && vis[arr[i]] == 0) {
				cnt--;
				// t.PB(arr[i]);
				vis[arr[i]] = 1;
			}
			if(cnt == 0) {
				cnt = k;
				group++;
				fill(all(vis),0);
				// for(auto&a:t)vis[a]=0;
				// t.clear();
			}
		}
		return (group >= m);
	}
	void solve() {
		i32 r = 0;
		for(auto i = 0 ; i < n ; ++i) {
			xin >> arr[i];
			r=max(r,arr[i]);
		}
		r++;
		r = min(r,  n+1);
		i32 l = 0;
		while(l < r) {
			int mid = (l+r+1)>>1;
			if(check(mid)) {
				l = mid;
			} else {
				r = mid-1;
			}
		}
		
		xout << l << '\n';
		return;
	}
	~solver() {
		IO::flush();
	}
};

signed main() {

	i32 n , m ;
	xin >> n >> m;
	solver s(n,m);
	s.solve();
	
	return 0;
}