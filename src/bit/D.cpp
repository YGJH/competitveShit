//https://vjudge.net/contest/694552#problem/D
#include <bits/stdc++.h>
#define int long long
using namespace std;


struct BIT{
    vector<int> bit;
    int sz ;
    BIT(int n):
        sz(n+1),
        bit(n+2 , 0) {};
    void update(int pos, int val) {
        while(pos < sz) {
            bit[pos] += val;
            pos += lowbit(pos);
        }
    }
    int qry(int pos) {
        int ret = 0;
        while(pos) {
            ret += bit[pos];
            pos -= lowbit(pos);
        }
        return ret;
    }
    inline int lowbit(int a) {
        return (a & -a);
    }
};

bool w = 0; char c;
template<typename T>
inline void re(T& a) {
    w=0;c = getchar();a = 0; while (c < '0' || c > '9') w |= (c == '-'), c = getchar();
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
signed main() {
    int n , q;
    re(n), re(q);
    vector<int> V(n+1);
    V[0] = 0;
    int u;
    BIT B(n+2);
    for(auto i = 1 ; i <= n ; i++) {
        re(V[i]);
        B.update(i , V[i] - V[i-1]);
    }
    int oper, a , b, k;
    while(q--) {
        re(oper);
        if(oper == 1) {
            re(a);re(b);re(u);
            B.update(a , u);
            B.update(b+1 , -u);
        }
        else {
            re(k);
            wr(B.qry(k));
            putchar('\n');
        }
    }
    return 0;
}