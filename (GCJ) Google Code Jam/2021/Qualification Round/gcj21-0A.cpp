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
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

void solve() {
    int n; cin >> n;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    
    int cost = 0;
    for (int i = 0; i < n-1; ++i) {
        int p = min_element(begin(v) + i, end(v)) - begin(v);
        reverse(begin(v) + i, begin(v) + p + 1);
        cost += p - i + 1;
    }
    cout << cost << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}