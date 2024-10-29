#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma G++ optimize(1)
#pragma G++ optimize(2)
#pragma G++ optimize(3)
#pragma G++ optimize("Ofast")
#pragma G++ optimize("inline")
#pragma G++ optimize("-fgcse")
#pragma G++ optimize("-fgcse-lm")
#pragma G++ optimize("-fipa-sra")
#pragma G++ optimize("-ftree-pre")
#pragma G++ optimize("-ftree-vrp")
#pragma G++ optimize("-fpeephole2")
#pragma G++ optimize("-ffast-math")
#pragma G++ optimize("-fsched-spec")
#pragma G++ optimize("unroll-loops")
#pragma G++ optimize("-falign-jumps")
#pragma G++ optimize("-falign-loops")
#pragma G++ optimize("-falign-labels")
#pragma G++ optimize("-fdevirtualize")
#pragma G++ optimize("-fcaller-saves")
#pragma G++ optimize("-fcrossjumping")
#pragma G++ optimize("-fthread-jumps")
#pragma G++ optimize("-funroll-loops")
#pragma G++ optimize("-fwhole-program")
#pragma G++ optimize("-freorder-blocks")
#pragma G++ optimize("-fschedule-insns")
#pragma G++ optimize("inline-functions")
#pragma G++ optimize("-ftree-tail-merge")
#pragma G++ optimize("-fschedule-insns2")
#pragma G++ optimize("-fstrict-aliasing")
#pragma G++ optimize("-fstrict-overflow")
#pragma G++ optimize("-falign-functions")
#pragma G++ optimize("-fcse-skip-blocks")
#pragma G++ optimize("-fcse-follow-jumps")
#pragma G++ optimize("-fsched-interblock")
#pragma G++ optimize("-fpartial-inlining")
#pragma G++ optimize("no-stack-protector")
#pragma G++ optimize("-freorder-functions")
#pragma G++ optimize("-findirect-inlining")
#pragma G++ optimize("-frerun-cse-after-loop")
#pragma G++ optimize("inline-small-functions")
#pragma G++ optimize("-finline-small-functions")
#pragma G++ optimize("-ftree-switch-conversion")
#pragma G++ optimize("-foptimize-sibling-calls")
#pragma G++ optimize("-fexpensive-optimizations")
#pragma G++ optimize("-funsafe-loop-optimizations")
#pragma G++ optimize("inline-functions-called-once")
#pragma G++ optimize("-fdelete-null-pointer-checks")
#include <bits/stdc++.h>
using namespace std;


constexpr int mxn = 2e5 + 3;
bool w = 0;
char c;
template <typename T>
inline void re(T& a)
{
    c = getchar();
    a = 0;
    while (c < '0' || c > '9')
        w |= (c == '-'), c = getchar();
    while (c >= '0' && c <= '9')
        a = (a << 1) + (a << 3) + (c & 15), c = getchar();
    if (w)
        a = -a;
    return;
}
char st[30];
int kkkk = 0;
template <typename T>
inline void wr(T a)
{
    kkkk = 0;
    if (a == 0)
    {
        putchar('0');
        return;
    }
    if (a < 0)
        putchar('-'), a = -a;
    while (a)
    {
        st[kkkk++] = a % 10 + '0', a /= 10;
    }
    while (kkkk)
    {
        putchar(st[--kkkk]);
    }
    return;
}
struct Edge {
    // int w , u ,v;
    int u, v, w;
    int tag;
    int num;
    Edge() {
        tag = 0;
    }
    bool operator<(const Edge& b) const {
        return w < b.w;
    }
    bool operator<(const Edge& b)  {
        return w < b.w;
    }
    bool operator==(const Edge& b) {
        return w == b.w && u == b.u && v == b.v;
    }
    bool operator()(const Edge& b) const {
        return w < b.w;
    }
    bool operator==(Edge& a)  {
        return w == a.w && v == a.v && w == a.w;
    }
    int operator()(const Edge &a) {
        return a.w;
    }

};
vector<Edge> que;
int f[mxn], sz[mxn];
int find(int x) {
    return (x == f[x]) ? x : f[x] = find(f[x]);
}
void merge(int x, int y) {
    int xx = find(x), yy = find(y);
    if (xx == yy) return;
    if (sz[xx] < sz[yy]) {
        swap(xx, yy);
    }
    f[yy] = xx;
    sz[xx] += sz[yy];
    return;
}
vector<Edge> E;
bitset<mxn> ans;
int cnt = 0;
// int con[mxn];
int mx = 0;
Edge tar;
void solve() {
    for (auto &a : E) {
        // cerr << a.u << ' ' << a.v << ' ' << a.w << ' ' << a.tag << endl;
        if (find(a.v) == find(a.u)) {
            if(a.tag) {
                ans[a.num]=0;
            }
        }
        else {
            if(a.tag) {
                ans[a.num]=1;
            }
            else{
                merge(a.v , a.u);
            }
        }
    }
    return;
}

signed main() {
    int n, m, q;
    re(n);
    re(m);
    re(q);
    tar.num = mxn - 3;
    tar.tag = 0;
    for (int i = 1; i <= n; i++) sz[i] = 1, f[i] = i;
    for (int i = 0; i < m; i++) {
        re(tar.u) ; re(tar.v) ; re(tar.w);
        if (tar.u == tar.v) continue;
        E.push_back(tar);
    }
    tar.tag = 1;
    for (int i = 0; i < q; i++) {
        re(tar.u), re(tar.v), re(tar.w);
        tar.num = i;
        E.push_back(tar);
    }
    sort(E.begin() , E.end());
    solve();
    for(int i = 0 ; i < q ; i++) {
        if(ans[i]) {
            puts("Yes");
        }
        else{
            puts("No");
        }
    }
    return 0;
}
