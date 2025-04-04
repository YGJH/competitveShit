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
template<typename T , typename... Args>
inline void read(T &a, Args&... args) {
read(a);  // 讀取第一個變數
read(args...);  // 讀取第一個變數
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
#define max(a ,b) (a>b)?a:b
struct Tag {
    // int l , r;
    int add;
    Tag(){add=0;}
    Tag(int a) {
        add = a;
    };
    Tag& operator+=(const Tag& a) {
        add += a.add;
        return *this;
    }
};
struct Info {
    int v , rightMost;
    Info(int a , int b):
    v(a),
    rightMost(b)
    {}
    Info(int a) {v = a;rightMost = -1;};
    Info(){v=0;rightMost = -1;};
};
Info merge(Info a , Info b) {
return Info(a.v + b.v , max(a.rightMost , b.rightMost));
}
int tmp;
int target = 0;
int lasPut = 0;
// [l, r)
// template<class Info, class Tag>
struct segTree {
    inline i32 cl(i32 x) { return x << 1; }
    inline i32 cr(i32 x) { return (x << 1) | 1; }
    i32 n;
    vector<Info> info;
    vector<Tag> tag;
    segTree(): n(0) {}
    segTree(i32 n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    segTree(vector<T> init_) {
        init(init_);
    }
    void init(i32 n_, Info v_ = Info()) {
        init(vector(n_, v_));
    }
    template<class T>
    void init(vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
        function<void(i32, i32, i32)> build = [&](i32 p, i32 l, i32 r) {
            if (r - l == 1) {
                info[p] = Info(init_[l].v , l);
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
        push(cl(p), l, m);
        push(cr(p), m, r);
        info[p] = merge(info[cl(p)], info[cr(p)]);
        info[p].v = max(info[p].v , 0);
        if(info[p].v == (r - l) && r - l > 1) {
            info[p].rightMost = -1;
        }
    }
    void rangeModify(i32 p, i32 l, i32 r, i32 x, i32 y, const Tag &v) {
        push(p, l, r);
        if (l >= x && r <= y) {
            tag[p] += v;
            return;
        }
        i32 m = (l + r) >> 1;
        if (x < m) rangeModify(cl(p), l, m, x, y, v);
        if (y > m) rangeModify(cr(p), m, r, x, y, v);
        pull(p, l, r);
    }
    Info rangeQuery(i32 p, i32 l, i32 r, i32 x, i32 y) {
        push(p, l, r);
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        i32 m = (l + r)>> 1;
        return merge(rangeQuery(cl(p), l, m, x, y), rangeQuery(cr(p), m, r, x, y));
    }
    Info rangeQuery(i32 l, i32 r) { return rangeQuery(1, 0, n, l, r); }
    void rangeModify(i32 l, i32 r, const Tag &v) { rangeModify(1, 0, n, l, r, v); }
    void push(i32 p, i32 l, i32 r) { // need compelete
        if (tag[p].add != 0) {
            info[p].v += tag[p].add * (r - l);
            info[p].v = max(0 , info[p].v);
            if (r - l != 1) {
                if(tag[cl(p)].add < 0) {
                    tag[cl(p)].add = tag[p].add;
                }
                if(tag[cr(p)].add < 0) {
                    tag[cr(p)].add = tag[p].add;
                }
            }
            tag[p].add = 0;
        }
    }
    int findFirst(int pos , int l , int r , int st) {
        if(l >= n || r <= st) return -1;
        push(pos, l, r);
        pull(pos, l, r);
        if(l >= st && r <= n && (r - l) - info[pos].v < target) {
            auto now = (r - l) - info[pos].v;
            if(now > 0) {
                de(info[pos].rightMost , l , r , now);
                lasPut = max(lasPut , info[pos].rightMost);
                target -= now;
                tmp += max( 0 , now ) ;
            }
            return -1;
        }
        if(r - l == 1) {
            de(info[pos].rightMost, l , r);
            lasPut = max(lasPut , info[pos].rightMost);
            return l;
        }
        int m = (l + r) >> 1;
        int ret = findFirst(cl(pos) , l , m , st);
        if(ret == -1) {
            return findFirst(cr(pos) , m , r , st);
        }
        return ret;
    }
    int findFirst(int st) {
        return findFirst(1 , 0 , n , st);
    }

};

void solve() {
    // auto cmp = [&](int l , int r ,Info a) {
    //     // de( (r - l) - a.v , target);
    //     return (r - l) - a.v > target;
    // };
    int n , m;
    read(n , m);
    int com , A , F;
    segTree seg((vector<Info>(n)));    
    for(int i = 0 ; i < m ; i++) {
        read(com);
        if(com == 1) {
            read(A,F);
            tmp = 0;
            lasPut = -1;
            target = F;
            int pos = seg.findFirst(A);
            de(A , F , tmp , pos , lasPut);
            if(A >= n || tmp <= 0) {
                write("Can not put any one.\n");
            } else {
                if(pos == -1 || pos >= n) {
                    write(A , ' ');
                    write(lasPut , '\n');
                    seg.rangeModify(A , n , -1e9);
                    seg.rangeModify(A , n , 1);
                } else {
                    write(A, ' ');
                    write(pos, '\n');
                    seg.rangeModify(A , pos+1 , -1e9);
                    seg.rangeModify(A , pos+1 , 1);
                }
            }
        } else {
            read(A , F);
            int ans = seg.rangeQuery(A , F+1).v;
            write(ans ,'\n');
            seg.rangeModify(A , min(n , F+1) , Tag(-1e9));
        }
    }
    return ;
    
}

signed main(){
    int t = 1;
    read(t);
    while(t--) {
        solve();
        write('\n');
    }
    IO::flush();
    return 0;

}
