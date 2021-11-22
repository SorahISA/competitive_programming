#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &x, T y) {return x > y ? x = y, 1 : 0;}
template<typename T> bool chmax(T &x, T y) {return x < y ? x = y, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    vector<int> garbage(366, 0);
    while (N--) {int tmp; cin >> tmp, garbage[tmp] = 1;}
    
    int sum = 0, left = 0, ans = 0;
    for (int i = 1; i <= 365; ++i) {
        if ((sum += left) >= 20) ++ans, sum = left = 0;
        left += garbage[i];
    }
    cout << ans + !!left << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}