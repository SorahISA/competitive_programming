#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

#define X first
#define Y second
#define eb emplace_back
#define SZ(x) ((int)(x).size())
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T>
bool chmin(T &x, T y) {
    if (x > y) return x = y, true;
    return false;
}

template<typename T>
bool chmax(T &x, T y) {
    if (x < y) return x = y, true;
    return false;
}

void solve() {
    int table[10][10];
    for (auto &vec : table) {
        for (auto &x : vec) cin >> x;
    }
    
    auto check = [&](int num, int div, int lst = 0) {
        while (div) lst = table[lst][num / div], num %= div, div /= 10;
        return lst;
    };
    
    vector<int> enc(10000);
    for (int i = 0; i <= 9999; ++i) enc[i] = 10 * i + check(i, 1000);
    
    int ans = 0;
    for (auto x : enc) {
        int flag = 0;
        for (int p = 1; p <= 10000 and !flag; p *= 10) {
            for (int n = 0; n <= 9 and !flag; ++n) {
                int y = x - (x/p % 10) * p + n * p;
                if (x != y and !check(y, 10000)) flag = 1;
            }
        }
        for (int p = 1, q = 10; q <= 10000 and !flag; p *= 10, q *= 10) {
            int y = x + (x/p % 10) * (q - p) + (x/q % 10) * (p - q);
            if (x != y and !check(y, 10000)) flag = 1;
        }
        ans += flag;
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
