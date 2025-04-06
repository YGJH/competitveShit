#pragma GCC optimize(1,2,3,"Ofast","inline")
#pragma GCC optimize("O3,unroll-loops")
#pragma G++ optimize(1,2,3,"Ofast","inline")
#pragma G++ optimize("O3,unroll-loops")
#include <iostream>
#include <vector>
#include <functional>
#include <stdint.h>
using namespace std;
#define int i32
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
#define max(a, b) (a > b) ? a : b
struct Tag {
    bool pending;    
	int add;
	Tag() { pending = 0; add = 0; }
	Tag(int a) { pending = 0;add = a; };
	Tag &operator+=(const Tag &a) {
		add += a.add;
		return *this;
	}
};
struct Info {
	int v, rightMost, leftMost;
	Info(int a, int b , int c) : v(a), rightMost(b),leftMost(c) {}
	Info(int a) {
		v = a;
		rightMost = -1;
		leftMost = -1;
	};
	Info() {
		v = 0;
		rightMost = -1;
        leftMost = -1;
	};
};
Info merge(Info a, Info b) {
    int lef = -1;
    if(a.leftMost != -1) lef = a.leftMost;
    else lef = b.leftMost;
    return Info(a.v + b.v, max(a.rightMost, b.rightMost) , lef);
}
int tmp;
int target = 0;
int lasPut = 0;
int lef;
// [l, r)
// template<class Info, class Tag>
struct segTree {
	inline i32 cl(i32 x) { return x << 1; }
	inline i32 cr(i32 x) { return (x << 1) | 1; }
	i32 n;
	vector<Info> info;
	vector<Tag> tag;
	segTree() : n(0) {}
	// segTree(i32 n_, Info v_ = Info()) { init(n_, v_); }
	segTree(vector<int> init_) { init(init_); }
	// void init(i32 n_, Info v_ = Info()) { init(vector(n_, v_)); }
    void init(vector<int> init_) {
		n = init_.size();
		info.assign(4 << __lg(n), Info());
		tag.assign(4 << __lg(n), Tag());
		function<void(i32, i32, i32)> build = [&](i32 p, i32 l, i32 r) {
			if (r - l == 1) {
				info[p] = Info(init_[l], l , l);
				return;
			}
			i32 m = (l + r) >> 1;
			build(cl(p), l, m);
			build(cr(p), m, r);
			pull(p, l, r);
		};
		build(1, 0, n);
	}
	void pull(i32 p, i32 l, i32 r) {
		i32 m = (l + r) >> 1;
        if(tag[cl(p)].pending)
            push(cl(p), l, m);
		
        if(tag[cr(p)].pending)
            push(cr(p), m, r);
		info[p] = merge(info[cl(p)], info[cr(p)]);		
	}
    void rangeModify(i32 p, i32 l, i32 r, i32 x, i32 y, const Tag &v) {
        // 如果存在懶標記，先下放它
        if (tag[p].pending) {
            push(p, l, r);
        }
        // 無交集時直接返回
        if (r <= x || l >= y)
            return;
        // 當前區間完全包含於 [x, y) 中，直接更新
        if (l >= x && r <= y) {
            tag[p] = v; 
            tag[p].pending = 1;
            if (r - l > 1) {
                tag[cl(p)].add = v.add;
                tag[cl(p)].pending = 1;
                tag[cr(p)].add = v.add;
                tag[cr(p)].pending = 1;
            }
			info[p].rightMost = (tag[p].add <= 0) ? (r-1):-1;
			info[p].leftMost = (tag[p].add <= 0) ? l:-1;
            return;
        }
        i32 m = (l + r) >> 1;
        if (x < m) rangeModify(cl(p), l, m, x, y, v);
        if (y > m) rangeModify(cr(p), m, r, x, y, v);
        pull(p, l, r);
    }
	Info rangeQuery(i32 p, i32 l, i32 r, i32 x, i32 y) {
        if(tag[p].pending)
            push(p, l, r);
		if (l >= y || r <= x) {
            return Info();
		}
		if (l >= x && r <= y) {
            return info[p];
		}
		i32 m = (l + r) >> 1;
		return merge(rangeQuery(cl(p), l, m, x, y),
            rangeQuery(cr(p), m, r, x, y));
	}
	inline Info rangeQuery(i32 l, i32 r) { return rangeQuery(1, 0, n, l, r); }
	inline void rangeModify(i32 l, i32 r, const Tag &v) {
        rangeModify(1, 0, n, l, r, v);
	}
    void push(i32 p, i32 l, i32 r) {
        if(tag[p].pending) {
            info[p].v = tag[p].add * (r - l);
			info[p].rightMost = (tag[p].add <= 0) ? r-1:-1;
            info[p].leftMost = (tag[p].add <= 0) ? l:-1;
            if (r - l != 1) {
                tag[cl(p)].add = tag[p].add;
                tag[cl(p)].pending = 1;
                tag[cr(p)].add = tag[p].add;
                tag[cr(p)].pending = 1;
            }
            tag[p].add = 0;
            tag[p].pending = 0;
        }
    }
	int findFirst(int pos, int l, int r, int st) {
		if (l >= n || r <= st || target <= 0)
			return -1;
        if(tag[pos].pending)
            push(pos , l , r);
		auto now = (r - l) - info[pos].v;
		if (l >= st && r <= n && now <= target && now > 0) {
            lasPut = max(lasPut, info[pos].rightMost);
            if(info[pos].leftMost != -1)
                lef = min(lef , info[pos].leftMost);
			target -= now;
			tmp += max(0, now);
			return -1;
		} else if(l >= st && r <= n && now <= target && now == 0) {
            return -1;
        }
		if (r - l == 1) {
            tmp += (info[pos].v == 0);
            if(info[pos].leftMost != -1)            
			    lef = min(lef, info[pos].leftMost);
            lasPut = max(lasPut , info[pos].rightMost);
            target -= now;
			return -1;
		}
		int m = (l + r) >> 1;
        int ret ;
        if(target > 0) {
		    ret = findFirst(cl(pos), l, m, st);
		    if (ret == -1) {
			    return findFirst(cr(pos), m, r, st);
            }
        }
		return ret;
	}
	int findFirst(int st) { return findFirst(1, 0, n, st); }
};
int ans;
void solve() {

	int n, m;
	read(n, m);
	int com, A, F;
	segTree seg((vector<int>(n,0)));
	while (m--) {
		read(com , A , F);
		if (com == 1) {
			tmp = 0;
			lasPut = -1;
			target = F;
            lef = n+1;
			int pos = seg.findFirst(A);
            // de(tmp , lef , lasPut , A , F);
			if (A >= n || lasPut == -1) {
                write("Can not put any one.\n");
                continue;
            } else {
                write(lef, ' ');
				write(lasPut, '\n');
                seg.rangeModify(lef, lasPut + 1, Tag(1));
                continue;
			}
		} else {
			ans = seg.rangeQuery(A, F + 1).v;
			write(ans, '\n');
			seg.rangeModify(A, min(n, F + 1), Tag(0));
            continue;
		}
	}
	return;
}

signed main() {

	int t = 1;
	read(t);
    // cin >> t;
	while (t--) {
		solve();
		write('\n');
        // cout << '\n';
    }
	IO::flush();
	return 0;
}
