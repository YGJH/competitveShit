#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;

// 計算 n 次單位根
vector<complex<double>> nthRootsOfUnity(int n) {
    vector<complex<double>> roots(n);
    // 計算角度，每個單位根的角度間隔為 2π/n
    double angle = 2 * M_PI / n;
    for (int k = 0; k < n; ++k) {
        roots[k] = complex<double>(cos(angle * k), sin(angle * k));
    }
    return roots;
}

int main() {
    int n = 8;  // 例如計算 8 次單位根
    auto roots = nthRootsOfUnity(n);
    
    // 輸出每一個單位根
    for (int k = 0; k < n; ++k) {
        cout << "Root " << k << ": " << roots[k] << endl;
    }
    
    return 0;
}
