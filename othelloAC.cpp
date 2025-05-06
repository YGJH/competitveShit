#pragma GCC optimize(1, 2, 3, "Ofast", "inline")
#pragma GCC optimize("O3,unroll-loops")
#pragma G++ optimize(1, 2, 3, "Ofast", "inline")
#pragma G++ optimize("O3,unroll-loops")
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

char aa[] = {'A', 'B', 'C', 'D', 'E', 'F'};
char aaa[] = {'a', 'b', 'c', 'd', 'e', 'f'};

int xx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int yy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
vector<vector<char>> board(6, vector<char>(6));
vector<vector<int>> ans(6, vector<int>(6, 0));

bool check(int i, int j) { return (i < 6 && i >= 0 && j < 6 && j >= 0); }
void modify(const char player, int y, int x,
			queue<pair<int, int>> &modified) {
	bool f = false;
	const char oppisChar = (player == 'O')?'X':'O';
	for(int i = 0 ; i < 8 ; i++) {
		int dr = yy[i];
		int dc = xx[i];
		int nr = dr + y;
		int nc = dc + x;
		while(check(nr , nc) && board[nr][nc] == oppisChar) {
			nr += dr;
			nc += dc;
		}
		if(check(nr , nc) && board[nr][nc] == player) {
			nr -= dr;
			nc -= dc;
			while(check(nr, nc) && board[nr][nc] == oppisChar) {
				modified.push({nr , nc});
				board[nr][nc] = player;
				nr -= dr;
				nc -= dc;
			}
		}
	}
	return ;
}

void find_next(queue<pair<int, int>> &que, const char player,
			   vector<vector<int>> &tmp) {// que return '+'
	vector<vector<bool>> vis(6, vector<bool>(6,false));
	const char openChar = (player=='O')?'X':'O';
	for(int i = 0 ; i < 6 ; ++i) {
		for(int j = 0 ; j < 6 ; ++j) {
			if(board[i][j] == player) {
				for(int k = 0 ; k < 8 ; k++) {
					bool f = 0;
					int dr = yy[k];
					int dc = xx[k];
					int nr = dr + i;
					int nc = dc + j;
					int cnt = 0;
					while(check(nr , nc) && board[nr][nc] == openChar) {
						f=1;
						nr += dr;
						nc += dc;
						cnt++;
					}
					if(f && check(nr , nc) && board[nr][nc] == '+' && vis[nr][nc] == false) {
						tmp[nr][nc] = cnt;
						que.push({nr , nc});
						vis[nr][nc] = 1;
					}

				}
			}
		}
	}
	// auto tt = que;
	// while(tt.empty() == 0) {
	// 	auto [yt,xt] = tt.front();tt.pop();
	// 	cerr << "(" << yt << ", " << xt << ")" << '\n';
	// }
	// cerr << '\n';


	return ;

}
struct node {
	int y, x;
	int score;
};
vector<node> ans_out;
int ans_depth;
char rootPlayer;
int bfs(const char player, const int depth,
		const bool status) { // status == true is max
	vector<vector<int>> value(6, vector<int>(6, 0));
	queue<pair<int, int>> que;
	// de(depth);
	if (depth <= 0) {
		int score = 0;
		for(int i = 0 ; i < 6 ; ++i) {
			for(int j = 0 ; j < 6 ; ++j) {
				if(board[i][j] == rootPlayer) {
					score++;
				} else if(board[i][j] != '+'){
					score--;
				}
			}
		}
		return score;
	} else {
		find_next(que, player , value);
		int ret = (status)?INT32_MIN:INT32_MAX;
		const char opisChar = (player=='O')?'X':'O';
		if(que.empty()) {
			int score = bfs(opisChar , depth-1 , !status);
			return score;
		}
		int besty = 0 , bestx = 0;
		while(que.empty()==0) {
			auto &[y,x] = que.front();que.pop();
			queue<pair<int,int>> modified;
			
			modify(player , y , x , modified);
			board[y][x] = player;
			// std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			int score = bfs(opisChar , depth - 1 , !status);
			while(modified.empty() == 0 ) {
				auto &[nr,nc] = modified.front() ; modified.pop();
				board[nr][nc] = opisChar;
			}
			board[y][x] = '+';

			if(depth == ans_depth) {
				ans[y][x] = score;
			}
			if(status) {
				if(ret < score) {
					bestx = x;
					besty = y;
					ret = score;
				}
			} else {
				if(ret > score) {
					bestx = x;
					besty = y;
					ret = score;
				}
			}
		}
		// if(player == rootPlayer)
		// 	ans_out.push_back({besty , bestx , ret});		
		if(ret <= INT32_MIN/2 || ret >= INT32_MAX/2) ret = 0 ;
		return ret;
	}
}

void solve() {
	string input;
	getline(cin, input);
	ans.assign(6, vector<int>(6, -1e9));
	while (input.length() <= 2)
		getline(cin, input);

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			board[i][j] = input[i * 6 + j];
		}
	}
	short player_C;
	int depth = 8;
	cin >> player_C >> depth;
	char player = (player_C == 2)?'O':'X';
	ans_depth = depth;
	rootPlayer = player;
	bfs(player , depth , 1);
	int out = INT32_MIN;
	int y = 0 , x = 0 ;
	for(int i = 0 ; i < 6 ; ++i) {
		for(int j = 0 ; j < 6 ; ++j) {
			if(out < ans[i][j]) {
				out = ans[i][j];
				y = i; x = j;
			}
		}
	}
	cout << '[' << aa[y] << aaa[x] << "]\n";
	return;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
