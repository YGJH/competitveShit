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
unordered_map<string, int> vis;
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
struct node {
    string first;
    short second;
    int step;
};
int cnt = 0;
void build(string &n) {
    queue<node> que;
    que.push({n,8,1});
    while(que.empty()==0) {
        auto tmp = que.front();que.pop();
        string now = tmp.first;
        short state = tmp.second;
        auto step = tmp.step+1;
        if(vis[now]!=0) {
            // de(vis[now] , step);
            vis[now] = min(vis[now] , step);
            continue;
        }
        cnt++;
        vis[now] = tmp.step;
        // de(state , now);
        // std::this_thread::sleep_for(std::chrono::milliseconds(400));
        switch(state) {
            case 0:
            {
                swap(now[0] , now[1]);
                que.push({now , 1 ,step});
                swap(now[0] , now[1]);
                swap(now[0] , now[3]);
                que.push({now , 3, step});
                // swap(now[0] , now[3]);
                break ;
            }
            case 1:
            {
                swap(now[1] , now[0]);
                que.push({now , 0, step});
                swap(now[1] , now[0]);
                swap(now[1] , now[2]);
                que.push({now , 2, step});
                swap(now[1] , now[4]);
                que.push({now , 4, step});
                // swap(now[1] , now[4]);
                break ;
            }
            case 2:
            {
                swap(now[2] , now[1]);
                que.push({now , 1, step});
                swap(now[2] , now[1]);
                swap(now[2] , now[5]);
                que.push({now , 5, step});
                // swap(now[2] , now[5]);
                break ;
            }
            case 3:
            {
                swap(now[3] , now[0]);
                que.push({now , 0, step});
                swap(now[3] , now[0]);
                swap(now[3] , now[4]);
                que.push({now , 4, step});
                swap(now[3] , now[4]);
                swap(now[3] , now[6]);
                que.push({now , 6, step});
                // swap(now[3] , now[6]);
                break ;
            }
            case 4:
            {
                swap(now[4] , now[1]);
                que.push({now , 1, step});
                swap(now[4] , now[1]);
                swap(now[4] , now[3]);
                que.push({now , 3, step});
                swap(now[4] , now[3]);
                swap(now[4] , now[5]);
                que.push({now , 5, step});
                swap(now[4] , now[5]);
                swap(now[4] , now[7]);
                que.push({now , 7, step});
                // swap(now[4] , now[7]);
                break ;
                
            }
            case 5:
            {
                swap(now[5] , now[2]);
                que.push({now , 2, step});
                swap(now[5] , now[2]);
                swap(now[5] , now[8]);
                que.push({now , 8, step});
                swap(now[5] , now[8]);
                swap(now[5] , now[4]);
                que.push({now , 4, step});
                // swap(now[5] , now[4]);
                break ;
            }
            case 6:
            {
                swap(now[6] , now[3]);
                que.push({now , 3, step});
                swap(now[6] , now[3]);
                swap(now[6] , now[7]);
                que.push({now , 7, step});
                // swap(now[6] , now[7]);
                break ;
            }
            case 7:
            {
                swap(now[7] , now[6]);
                que.push({now , 6, step});
                swap(now[7] , now[6]);
                swap(now[7] , now[8]);
                que.push({now , 8, step});
                swap(now[7] , now[8]);
                swap(now[7] , now[4]);
                que.push({now , 4, step});
                // swap(now[7] , now[4]);
                break ;
            }
            case 8:
            {
                swap(now[8] ,now[5]);
                que.push({now , 5, step});
                swap(now[8] ,now[5]);
                swap(now[8] ,now[7]);
                que.push({now , 7, step});
                // swap(now[8] ,now[7]);
                break ;
            }
        }
    }
}
signed main() {
    int cas = 1;
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;
    cin >> t;
    string init = "123456780";
    build(init);
    string tmp;
    string tt;
    tmp.reserve(10);
    tt.reserve(10);
    // de(cnt);
    while(t--) {
        tmp.clear();
        for(int i = 0 ; i < 3 ;i++){
            getline(cin , tt);
            if(tt.length() < 3){
                i--;
                continue;
            }
            for(int j = 0 ; j < tt.length() ; j++) {
                if(tt[j] != ' ')
                tmp.push_back(tt[j]);
            }
        }
        // de(tmp);
        if(vis[tmp] == 0) {
            cout << "Case " << cas++ << ": impossible" << '\n';
        }
        else {
            cout << "Case " << cas++ << ": " << vis[tmp]-1 << '\n';
        }
    }
    return 0;
}