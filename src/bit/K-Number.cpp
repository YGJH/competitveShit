#include <iostream>
using namespace std;

const int MAX = 100000;  // 数值范围：1 ~ 100000

int BIT[MAX + 1];        // 树状数组，存储前缀和信息
int freq[MAX + 1];       // 辅助数组，用于记录每个数的当前频次

// 返回 x 的最低位 1 的值
inline int lowbit(int x) {
    return x & (-x);
}

// 更新 BIT：在下标 idx 处增加 delta
void update(int idx, int delta) {
    for (; idx <= MAX; idx += lowbit(idx))
        BIT[idx] += delta;
}

// 查询 BIT 前缀和：[1, idx]
int query(int idx) {
    int sum = 0;
    for (; idx > 0; idx -= lowbit(idx))
        sum += BIT[idx];
    return sum;
}

// 利用二分查找在 BIT 中查找第 target 个数所在的位置
int binarySearch(int target) {
    int pos = 0;
    // 1<<17 = 131072，大于 MAX
    for (int i = 1 << 17; i > 0; i >>= 1) {
        if (pos + i <= MAX && BIT[pos + i] < target) {
            target -= BIT[pos + i];
            pos += i;
        }
    }
    return pos + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m;
    // 注意：每组测试数据的第一行为操作数 m
    while (cin >> m) {
        // 重置 BIT 和 freq 数组
        for (int i = 0; i <= MAX; i++) {
            BIT[i] = 0;
            freq[i] = 0;
        }
        
        while (m--) {
            int op;
            cin >> op;
            if (op == 0) {  // 插入操作
                int e;
                cin >> e;
                update(e, 1);
                freq[e]++;
            } else if (op == 1) {  // 删除操作
                int e;
                cin >> e;
                if (freq[e] <= 0) {
                    cout << "No Elment!" << "\n";
                } else {
                    update(e, -1);
                    freq[e]--;
                }
            } else if (op == 2) {  // 查询操作
                int a, k;
                cin >> a >> k;
                // 计算所有大于 a 的元素个数
                int total = query(MAX);
                int cnt = total - query(a);
                if (cnt < k) {
                    cout << "Not Find!" << "\n";
                } else {
                    int target = query(a) + k;
                    int ans = binarySearch(target);
                    cout << ans << "\n";
                }
            }
        }
    }
    
    return 0;
}
