#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n): p(n,-1), r(n,0) { iota(p.begin(), p.end(), 0); }
    int find(int x){ return p[x]==x ? x : p[x]=find(p[x]); }
    void unite(int a, int b){
        a = find(a); b = find(b);
        if (a==b) return;
        if (r[a]<r[b]) swap(a,b);
        p[b]=a;
        if (r[a]==r[b]) r[a]++;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double X, Y;
    int N;
    cin >> X >> Y;
    cin >> N;
    vector<pair<double,double>> P(N);
    for(int i=0;i<N;i++){
        cin >> P[i].first >> P[i].second;
    }

    // 檢查在半徑 d 下是否被封鎖
    auto blocked = [&](double d)->bool {
        DSU uf(N + 4);
        int LEFT = N, RIGHT = N+1, BOTTOM = N+2, TOP = N+3;

        // 圓與圓聯通
        for(int i=0;i<N;i++){
            for(int j=i+1;j<N;j++){
                double dx = P[i].first - P[j].first;
                double dy = P[i].second - P[j].second;
                if (dx*dx + dy*dy < 4*d*d) {
                    uf.unite(i,j);
                }
            }
        }
        // 圓與邊界聯通
        for(int i=0;i<N;i++){
            double x = P[i].first, y = P[i].second;
            if (x - d < 0)    uf.unite(i, LEFT);
            if (x + d > X)    uf.unite(i, RIGHT);
            if (y - d < 0)    uf.unite(i, BOTTOM);
            if (y + d > Y)    uf.unite(i, TOP);
        }

        // 只要有下列任一對邊界被聯通，就代表路徑被切斷
        if (uf.find(LEFT)   == uf.find(RIGHT))   return true;
        if (uf.find(BOTTOM) == uf.find(TOP))     return true;
        if (uf.find(LEFT)   == uf.find(BOTTOM))  return true;
        if (uf.find(RIGHT)  == uf.find(TOP))     return true;

        return false;  // 自由空間仍連通
    };

    // 二分搜尋
    double lo = 0, hi = max(X,Y);
    for(int it=0; it<60; it++){
        double mid = (lo + hi)/2;
        if (!blocked(mid))   // 未被封鎖，還能走得動
            lo = mid;
        else
            hi = mid;
    }

    cout << fixed << setprecision(6) << lo << "\n";
    return 0;
}
