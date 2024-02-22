#include <bits/stdc++.h>
#define mk make_pair
#define pb push_back
#define all(x) (x).begin(),(x).end()
#define ishowspeed ios_base::sync_with_stdio(0),cin.tie(nullptr);
#define ll long long
#define endl '\n'
#define lcm(a , b) (a * b) / __gcd(a ,b)
#define pause printf("Press any key to continue...\n") , fgetc(stdin);
#define int long long
using namespace std;


typedef struct Binary_Indexed_Tree{
    int n;
    vector<long long> bit;
    int lowbit(int x){// 0沒有lowbit
        return x&-x;
    }
    void init(int _n){
        n = _n+1;
        bit = vector<long long>(n+1,0);
    }
    void update(int x,int v){
        for(; x<n; x+=lowbit(x)){
            bit[x] += v;
        }
    }
    long long query(int x){
        long long ret = 0;
        for(; x>0; x-=lowbit(x)){
            ret += bit[x];
        }
        return ret;
    }
}BIT;


inline int poww(int a , int b) {
    int ret = 1;
    for( ; b ; b >>= 1 , a *= a) {
        if(b &  1) {
            ret *= a;
        }
    }
    return ret;
}

template<class io>
inline void re(io &x) {
    io c = getchar();int w = 0 ; x = 0;
    while(c < 48 || c > 57) w|=c==45,c=getchar();
    while(c > 47 && c < 58)x=(x<<3)+(x<<1)+(c&15),c=getchar();
    x=w?-x:x;return;
}
inline void wr(int x) {
    if(x < 0) 
        putchar('-'), x=~x,x++;
  static int sta[300];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) putchar(sta[--top] + 48);  // 48 是 '0'
}

inline int mmax(int x ,int y){
    return x > y ? x : y ;
}
inline int mmin(int x ,int y){
    return x < y?x:y;
}

bool const operator == (pair<int,int> &a , pair<int,int> &b){
    if(a.first==b.first && a.second == b.second) return true;
    else return false;
}

signed main() {
    // mt19937 mt(chrono::steady_clock::now().time_since_epoch().count());
    // uniform_int_distribution<> gen(1 , 10);
    int n , q;
    re(n) , re(q);
    BIT bt; bt.init(n+1);
    for(int i = 1; i <= n ; i++) {
        int tmp; re(tmp);
        bt.update(i , tmp);
    }
    // for(int i = 0 ; i <= n ; i++) {
    //     cout << bt.query(i) << endl;;
    // }
    for(int i = 0 ; i < q; i++) {
        int com , st , en; re(com), re(st) , re(en);
        if(com == 0) {
            bt.update(st + 1, en);
        }
        else {
            int kk = bt.query(en);
            int pp = bt.query(st);
            wr(kk - pp);
            putchar('\n');
        }
    }

    return 0;
}
