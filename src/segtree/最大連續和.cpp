//https://vjudge.net/contest/702395#problem/G
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    int length, prefix, suffix, maxi;
    char left, right;
};

int n, m;
string s;
vector<Node> segTree;

Node combine(const Node &L, const Node &R) {
    Node parent;
    parent.length = L.length + R.length;
    parent.left = L.left;
    parent.right = R.right;
    
    // Compute prefix
    parent.prefix = L.prefix;
    if (L.prefix == L.length && L.right == R.left) {
        parent.prefix = L.length + R.prefix;
    }
    
    // Compute suffix
    parent.suffix = R.suffix;
    if (R.suffix == R.length && L.right == R.left) {
        parent.suffix = R.length + L.suffix;
    }
    
    // Compute maximum contiguous same bit segment
    parent.maxi = max(L.maxi, R.maxi);
    if (L.right == R.left)
        parent.maxi = max(parent.maxi, L.suffix + R.prefix);
    
    return parent;
}

void build(int idx, int l, int r) {
    if (l == r) {
        segTree[idx] = {1, 1, 1, 1, s[l-1], s[l-1]};
        return;
    }
    int mid = (l + r) / 2;
    build(idx*2, l, mid);
    build(idx*2+1, mid+1, r);
    segTree[idx] = combine(segTree[idx*2], segTree[idx*2+1]);
}

void update(int idx, int l, int r, int pos) {
    if (l == r) {
        // Flip the bit at position pos.
        s[l-1] = (s[l-1] == '0' ? '1' : '0');
        segTree[idx] = {1, 1, 1, 1, s[l-1], s[l-1]};
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(idx*2, l, mid, pos);
    else
        update(idx*2+1, mid+1, r, pos);
    segTree[idx] = combine(segTree[idx*2], segTree[idx*2+1]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> s;
    n = s.size();
    cin >> m;
    
    segTree.resize(4*n);
    build(1, 1, n);
    
    while(m--) {
        int pos;
        cin >> pos;
        update(1, 1, n, pos);
        cout << segTree[1].maxi << "\n";
    }
    
    return 0;
}
