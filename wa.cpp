#include <bits/stdc++.h>
using namespace std;



bool w = 0; char c;
template<typename T>
inline void re(T& a) {
    w=0;c = getchar();a = 0; while ((c < '0' || c > '9') && c != EOF) w |= (c == '-'), c = getchar();
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
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n , c;
    cin >> n >> c;
    vector<pair<double,double>> V(n);
    for(auto &a : V) {
        cin >> a.first >> a.second;
    }
    sort(V.begin() , V.end() , [&](auto &a , auto &b) {
        return a.first/a.second > b.first/b.second;
    });
    double ans = 0, now = 0;
    for(int i = 0 ; i < n ; i++) {
        if(now + V[i].second <= c) {
            ans += V[i].first;
            now += V[i].second;
        } else {
            ans += (V[i].first / V[i].second) * (c-now);
            now = c;
            break;
        }
    }
    cout << setprecision(6) << fixed << ans << '\n';


    return 0;
}