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
struct node {
    string first;
    short second;
    int step;
    char move; // 0 up 1 down 2 left 3 right
};
#define min(a,b) (a<b)?a:b
// int cnt = 0;

unordered_map<string, int> vis;
unordered_map<string, char> fa;
inline bool check(string&a) {
    return vis[a] == 0;
}
vector<pair<string,int>> ans;
void build(string &n) {
    queue<node> que;
    que.push({n,0,0 , '9'});
    while(que.empty()==0) {
        auto tmp = que.front();que.pop();
        string now = tmp.first;
        auto state = tmp.second;
        auto step = tmp.step+1;
        fa[now] = tmp.move;
        // de(tmp.move , fa[now]);
        // std::this_thread::sleep_for(std::chrono::milliseconds(300));
        vis[now] = step;
        switch(state) {
            case 0:
            {
                swap(now[0] , now[1]);
                if(check(now))
                que.push({now , 1 ,step , '3'});
                swap(now[0] , now[1]);
                swap(now[0] , now[3]);
                if(check(now))
                que.push({now , 3, step , '1'});
                // swap(now[0] , now[3]);
                break ;
            }
            case 1:
            {
                swap(now[1] , now[0]);
                if(check(now))
                que.push({now , 0, step , '2'});
                swap(now[1] , now[0]);
                swap(now[1] , now[2]);
                if(check(now))
                que.push({now , 2, step , '3'});
                swap(now[1] , now[2]);
                swap(now[1] , now[4]);
                if(check(now))
                que.push({now , 4, step , '1'});
                // swap(now[1] , now[4]);
                break ;
            }
            case 2:
            {
                swap(now[2] , now[1]);
                if(check(now))
                que.push({now , 1, step , '2'});
                swap(now[2] , now[1]);
                swap(now[2] , now[5]);
                if(check(now))
                que.push({now , 5, step , '1'});
                // swap(now[2] , now[5]);
                break ;
            }
            case 3:
            {
                swap(now[3] , now[0]);
                if(check(now))
                que.push({now , 0, step , '0'});
                swap(now[3] , now[0]);
                swap(now[3] , now[4]);
                if(check(now))
                que.push({now , 4, step , '3'});
                swap(now[3] , now[4]);
                swap(now[3] , now[6]);
                if(check(now))
                que.push({now , 6, step , '1'});
                // swap(now[3] , now[6]);
                break ;
            }
            case 4:
            {
                swap(now[4] , now[1]);
                if(check(now))
                que.push({now , 1, step , '0'});
                swap(now[4] , now[1]);
                swap(now[4] , now[3]);
                if(check(now))
                que.push({now , 3, step , '2'});
                swap(now[4] , now[3]);
                swap(now[4] , now[5]);
                if(check(now))
                que.push({now , 5, step , '3'});
                swap(now[4] , now[5]);
                swap(now[4] , now[7]);
                if(check(now))
                que.push({now , 7, step , '1'});
                // swap(now[4] , now[7]);
                break ;
                
            }
            case 5:
            {
                swap(now[5] , now[2]);
                if(check(now))
                que.push({now , 2, step , '0'});
                swap(now[5] , now[2]);
                swap(now[5] , now[4]);
                if(check(now))
                que.push({now , 4, step , '2'});
                swap(now[5] , now[4]);
                swap(now[5] , now[8]);
                if(check(now))
                que.push({now , 8, step , '1'});
                // swap(now[5] , now[8]);
                break ;
            }
            case 6:
            {
                swap(now[6] , now[3]);
                if(check(now))
                que.push({now , 3, step , '0'});
                swap(now[6] , now[3]);
                swap(now[6] , now[7]);
                if(check(now))
                que.push({now , 7, step , '3'});
                // swap(now[6] , now[7]);
                break ;
            }
            case 7:
            {
                swap(now[7] , now[4]);
                if(check(now))
                que.push({now , 4, step , '0'});
                swap(now[7] , now[4]);
                swap(now[7] , now[6]);
                if(check(now))
                que.push({now , 6, step , '2'});
                swap(now[7] , now[6]);
                swap(now[7] , now[8]);
                if(check(now))
                que.push({now , 8, step , '3'});
                // swap(now[7] , now[8]);
                break ;
            }
            case 8:
            {
                swap(now[8] ,now[5]);
                if(check(now))
                que.push({now , 5, step , '0'});
                swap(now[8] ,now[5]);
                swap(now[8] ,now[7]);
                if(check(now))
                que.push({now , 7, step , '2'});
                // swap(now[8] ,now[7]);
                break ;
            }
        }
    }
}

void trackBack(string &now) {
    // std::this_thread::sleep_for(std::chrono::milliseconds(300));
    while(now != "012345678") {
        char move = fa[now];
        int state = 0;
        for(; state < 9 ; state++) if(now[state] == '0') break;
        switch (move)
        {
            case '0':
                {
                    cout << "move 0 to down" << endl;
                    swap(now[state], now[state + 3]);
                    break;
                }
            case '1':
                {
                    cout << "move 0 to up" << endl;
                    swap(now[state], now[state - 3]);
                    break;
                }
            case '2':
                {
                    cout << "move 0 to right" << endl;
                    swap(now[state], now[state+1]);
                    break;
                }
            case '3':
                {
                    cout << "move 0 to left" << endl;
                    swap(now[state], now[state-1]);
                    break;
                }
        }
        // cout << now << endl;
    }
}
void possible(string &now) {
    int state = 0;
    for(; state < 9 ; state++) if(now[state] == '0') break;
    switch(state) {
        case 0:
        {
            cout << '2' << endl;
            swap(now[0] , now[3]);
            cout << "move 0 to down" << endl << now << endl;
            swap(now[0] , now[3]);
            swap(now[0] , now[1]);
            cout << "move 0 to right" << endl << now << endl;
            swap(now[0] , now[1]);
            break ;
        }
        case 1:
        {
            cout << '3' << endl;
            swap(now[1] , now[4]);
            cout << "move 0 to down" << endl << now << endl;
            swap(now[1] , now[4]);
            swap(now[1] , now[0]);
            cout << "move 0 to left" << endl << now << endl;
            swap(now[1] , now[0]);
            swap(now[1] , now[2]);
            cout << "move 0 to right" << endl << now << endl;
            swap(now[1] , now[2]);
            break ;
        }
        case 2:
        {
            cout << '2' << endl;
            
            swap(now[2] , now[5]);
            cout << "move 0 to down" << endl << now << endl;

            swap(now[2] , now[5]);
            swap(now[2] , now[1]);
            cout << "move 0 to left" << endl << now << endl;
            
            swap(now[2] , now[1]);
            break ;
        }
        case 3:
        {
            cout << '3' << endl;
            swap(now[3] , now[0]);
            cout << "move 0 to up" << endl << now << endl;

            swap(now[3] , now[0]);

            swap(now[3] , now[6]);
            cout << "move 0 to down" << endl << now << endl;

            swap(now[3] , now[6]);
            swap(now[3] , now[4]);
            cout << "move 0 to right" << endl << now << endl;

            swap(now[3] , now[4]);
            break ;
        }
        case 4:
        {
            cout << '4' << endl;
            swap(now[4] , now[1]);
            cout << "move 0 to up" << endl << now << endl;

            swap(now[4] , now[1]);
            swap(now[4] , now[7]);
            cout << "move 0 to down" << endl << now << endl;
            
            swap(now[4] , now[7]);
            swap(now[4] , now[3]);
            cout << "move 0 to left" << endl << now << endl;

            swap(now[4] , now[3]);
            swap(now[4] , now[5]);
            cout << "move 0 to right" << endl << now << endl;

            swap(now[4] , now[5]);
            

            break ;
            
        }
        case 5:
        {
            cout << '3' << endl;
            swap(now[5] , now[2]);
            cout << "move 0 to up" << endl << now << endl;

            swap(now[5] , now[2]);
            swap(now[5] , now[8]);
            cout << "move 0 to down" << endl << now << endl;

            swap(now[5] , now[8]);
            swap(now[5] , now[4]);
            cout << "move 0 to left" << endl << now << endl;

            swap(now[5] , now[4]);
            break ;
        }
        case 6:
        {
            cout << '2' << endl;
            swap(now[6] , now[3]);
            cout << "move 0 to up" << endl << now << endl;
            swap(now[6] , now[3]);
            swap(now[6] , now[7]);
            cout << "move 0 to right" << endl << now << endl;
            swap(now[6] , now[7]);
            break ;
        }
        case 7:
        {
            cout << '3' << endl;
            swap(now[7] , now[4]);
            cout << "move 0 to up" << endl << now << endl;
            swap(now[7] , now[4]);
            swap(now[7] , now[6]);
            cout << "move 0 to left" << endl << now << endl;
            swap(now[7] , now[6]);
            swap(now[7] , now[8]);
            cout << "move 0 to right" << endl << now << endl;
            swap(now[7] , now[8]);
            break ;
        }
        case 8:
        {
            cout << '2' << endl;
            swap(now[8] ,now[5]);
            cout << "move 0 to up" << endl << now << endl;
            swap(now[8] ,now[5]);
            swap(now[8] ,now[7]);
            cout << "move 0 to left" << endl << now << endl;
            swap(now[8] ,now[7]);
            break ;
        }
    }
}

int manhattan(string &n) {
    int ret = 0;
    for(int i = 0 ; i < 9 ; i++) {
        if(n[i] == '0') continue;
            ret += abs(i/3 - (n[i]-'0')/3) + abs((i%3) - ((n[i]-'0')%3));
        
    }
    return ret;
}
signed main() {
    // ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    // int t;
    // cin >> t;
    string init = "012345678";
    build(init);
    string tmp;
    tmp.reserve(10);
    // de(t);
    // while(t--) {
    getline(cin , tmp);
    while(tmp.length() < 3) {
        getline(cin , tmp);
    }
    // de(vis[tmp]);
    if(vis[tmp] == 1) {
        puts("It is the goal state.");
        return 0;
    }
    // cout << manhattan(tmp) << endl;
    if(vis[tmp] != 0) {
        trackBack(tmp);
    } else {
        puts("No solution!!");
    }
        // possible(tmp);
    // }
    return 0;
}