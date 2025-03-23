#include <bits/stdc++.h>

using namespace std;

struct Node {
    string state;
    int g;
    int h;
    int f;
    long long time;
};

struct NodeComparator {
    bool operator()(const Node &a, const Node &b) const {
        if (a.f != b.f)
            return a.f > b.f;
        return a.time > b.time;
    }
};

int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);
    // int T; 
    priority_queue<Node, vector<Node>, NodeComparator> pq;
    long long timestamp = 0; 
    string op;
    while (cin>>op) {
        while(op.length() <= 1) {
            cin >> op;
        }
        if (op == "enqueue") {
            Node node;
            cin >> node.state >> node.g >> node.h;
            node.f = node.g + node.h;
            node.time = timestamp++;  
            pq.push(node);
            puts("Insert OK!");
        } else if (op == "dequeue") {
            if (pq.empty()) {
                puts("Queue is empty!!");
            } else {
                Node top = pq.top();
                pq.pop();
                cout << "Got " << top.state << "\n";
            }
        }
    }
    return 0;
}
