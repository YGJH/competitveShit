#include <iostream>
#include <string>
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
int main() {
    int T;
    cin >> T;
    while (T--) {
        long long n;
        cin >> n;
        de(n);
        long long lo = 0, hi = n - 1;
        while (lo < hi) {
            long long mid = (lo + hi + 1) / 2;
            cout << "READ " << mid << endl;
            fflush(stdout);
            string res;
            cin >> res;
            if (res == "true") {
                lo = mid;
            } else { 
                hi = mid - 1;
            }
        }
        cout << "OUTPUT " << lo << endl;
        fflush(stdout);
    }
    return 0;
}
