#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;
struct node {
    int u , v;
    int w;
    node (int u_ , int v_ , int w_) {
        u = u_;
        v = v_;
        w = w_;
    }
	bool operator<(const node &a) const {
		return w < a.w;
	}
};
node eval(const node &a , const node &b) {
	// if(a.u == 0 || a.v == 0 || b.v == 0 || b.u == 0) return node(0,0,INF);
	return node(a.u , b.v , a.u * b.v * b.u);
}

vector<pair<int,int>> s;
signed main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin >> n;
    int u , v ;
    vector<vector<node>> dp(n+1, vector<node>(n+1 , node(0 , 0 ,INF)));
    for(int i = 1 ; i <= n ; ++i) {
        cin >> u >> v;
        dp[i][i] = node(u , v ,0);
    }
    for(int i = 1 ; i <= n ; ++i) {
        for(int j = 1 ; j <= n - i ; ++j) {
			for(int k = j ; k + 1 <= j + i ; ++k) {
				// printf("now i = %d from %d to %d merge (%d, %d) to (%d, %d)\n" ,i , j , i+j , j, k , k+1, i+j);
				node tmp = eval(dp[j][k] , dp[k+1][j+i]); tmp.w += dp[k+1][i+j].w + dp[j][k].w;
				if(tmp < dp[j][i+j]) {
					dp[j][i+j] = tmp;
				}
				// printf("eval = (%lld, %lld, %lld)\n" , eval(dp[j][k] , dp[k+1][j+i]).u , eval(dp[j][k] , dp[k+1][j+i]).v , eval(dp[j][k] , dp[k+1][j+i]).w );
			}

        }
    }
	// for(int i = 1 ; i <= n ; ++i) {
	// 	for(int j = 1 ; j <= n ; ++j) {
	// 		printf("%4lld " ,dp[i][j].w);
	// 	}
	// 	printf("\n");
	// }
	cout << dp[1][n].w << '\n';
}

