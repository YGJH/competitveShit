#include <bits/stdc++.h>
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
// using P32 = pair<i32, i32>;
// using P64 = pair<i64, i64>;
const i64 INF = 1e18;
const ld eps = 1e-8L;

using namespace std;
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

int mex(vector<int> &v , int l , int r) {
    
    for(; l <= r ; l++) {
        if(v[l] == 0) return 1;
    }
    return 0;
}
void solve() {
    int n;
    cin >> n;
    vector<int> V(n);
    for(auto &a : V) {
        cin >> a;
    }
    vector<pair<int,int>> ans;
    while(V.size() > 1) {
        bool NoZero = 1;
        int l = -1,  r = -1;
        // orange(all(V));
        for(int i = V.size() - 1 ; i >= 0 && r==-1; i--) {
            if(V[i] == 0) {
                NoZero = 0;
                r = i;
                while(i >= 0 && V[i] == 0) {
                    l=i;
                    i--;
                }
            }
        }
        if(l == r) {
            if(r + 1 < V.size()) {
                r++;
            } else {
                l--;
            }
        }
        // de(NoZero , l , r);
        if(NoZero) {
            ans.push_back({1, V.size()});
            break;
        } else if(r == V.size() -1 && l == 0) {
            int n = V.size();
            int m = n / 2;
            ans.push_back({1, m}); n -= m;
            ans.push_back({1 , n});
            ans.push_back({1, 2});
            break;
        } else {
            if(r == -1) {
                ans.push_back({1, 2});
                vector<int> tmp = { mex(V , 0 , 1) };
                tmp.reserve(V.size());
                for(int i = 2 ; i < V.size() ; i++) {
                    tmp.push_back(V[i]);
                }
                V = tmp;
            }
            else {
                {
                    int nl = min(l ,r);
                    int nr = max(l ,r);
                    l = nl;
                    r = nr;
                }
                int me = mex(V , l , r);

                // de(l , r);
                ans.push_back({l+1 , r+1});
                vector<int> tmp; tmp.reserve(V.size());
                for(int i = 0 ; i < l ; i++) {
                    tmp.push_back(V[i]);
                }
                tmp.push_back(me);//de(me);
                for(int i = r + 1 ; i < V.size() ; i++) {
                    tmp.push_back(V[i]);
                }
                V = tmp;
            }
        }
    }
    cout << ans.size() << endl;
    for(auto &a : ans) {
        cout << a.first << ' ' << a.second << endl;
    }
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) {
        solve();
    }


    return 0;
}
