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
#define ef push_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) (int)(x).size()
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    int ans = 1;
    for (int i = 1; i <= N; ++i) {
        int tmp; cin >> tmp;
        chmax(ans, tmp - i + 1);
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
