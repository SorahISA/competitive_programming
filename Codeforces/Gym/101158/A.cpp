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
    int N, M; cin >> N >> M;
    
    vector<int> arr(M);
    for (auto &x : arr) cin >> x;
    reverse(ALL(arr));
    
    vector<int> app(N+1, 0);
    for (auto x : arr) {
        if (!app[x]) cout << x << "\n";
        app[x] = 1;
    }
    for (int i = 1; i <= N; ++i) {
        if (!app[i]) cout << i << "\n";
        app[i] = 1;
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
