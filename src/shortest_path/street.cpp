#include <bitset>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <stdint.h>
#include <vector>
using namespace std;
#define fk puts("幹你娘幹你娘幹你娘幹你娘");
// #define int i64
#define sfi(i) scanf("%d",&i)
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
struct cube {
	double min_x, max_x, min_y, max_y;
};
struct node {
	double len;
	double end_y;
    int id;
};
struct cmp {
	bool operator()(const node &a, const node &b) { return a.len > b.len; }
};

inline double gap(double minA, double maxA, double minB, double maxB) {
	if (maxA >= minB && maxB >= minA) {
		return 0.0;
	}
	return std::max(minB - maxA, minA - maxB);
}

bitset<200> vis;
// 計算兩個正方體的最短距離
inline double distanceBetweenCubes(const cube &a, const cube &b) {
	double dx = gap(a.min_x, a.max_x, b.min_x, b.max_x);
	double dy = gap(a.min_y, a.max_y, b.min_y, b.max_y);
	return std::sqrt(dx * dx + dy * dy);
}
void solve() {
	int n;
    double  w, h;
	vis.reset();
	cin >> n >> h >> w;
    // scanf("%d %lf %lf", &n , &w, &h);
    // fprintf(stderr, "%d %lf %lf" , n , w , h);
	double hh, ww, dis;
	int tmp;
	vector<cube> block;
	for (int i = 0; i < n; i++) {
		cin >> hh >> ww >> dis >> tmp;
        // scanf("%lf %lf %lf %d" , &hh , &ww , &dis, &tmp);
		if (tmp == 0) {
			block.push_back({0, ww, dis, dis + hh});
		} else {
			block.push_back({w - ww, w, dis, dis + hh});
		}
	}
	priority_queue<node, vector<node>, cmp> que; // length , end_y
	vector<vector<node>> E(n + 1);				 // len , now_point
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (i == j) {
				que.push({(block[i].min_y), block[i].max_y, i});
			} else {
				auto dis_t = distanceBetweenCubes(block[i], block[j]);
				auto mx_y = max(block[i].max_y, block[j].max_y);
				E[i].push_back({dis_t, mx_y, j});
				E[j].push_back({dis_t, mx_y, i});
			}
		}
		// E[i].push_back({h - block[i].max_y , h , 0});
	}
	block.clear();
	while (que.empty() == 0) {
		auto now = que.top();
		que.pop();
		de(now.id);
		if (now.end_y >= h) {
            cout << setprecision(6) << fixed << now.len << endl;
            // printf("%.6lf\n",now.len);
			return;
		}

		if (!vis[now.id]) {
			vis[now.id] = 1;
			que.push({h - now.end_y + now.len, h, -1});
		} else {
			continue;
		}
		if (now.id == -1)
			return;
		if (E[now.id].empty() == 0) {
			for (auto &e : E[now.id]) {
				que.push({e.len + now.len, e.end_y, e.id});
			}
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    freopen("street.in","r",stdin);
	int t;
    cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}