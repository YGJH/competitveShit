#include <bits/stdc++.h>
using namespace std;

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
struct node{
    int a, b , c;
}
signed main() {
    int n , k;
    re(n) , re(k);
    vector<node> A(n);
    for(auto &a : A) {
        re(a.a) , re(a.b) , re(a.c);
    }
    



    return 0;
}