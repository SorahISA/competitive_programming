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
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

const int mod = 1E9 + 7;

void solve() {
    int N; cin >> N;
    
    vector<int> vec(N), pre(N);
    for (auto &x : vec) cin >> x;
    partial_sum(ALL(vec), begin(pre));
    
    int ans = 0;
    for (int i = 1; i < N; ++i) ans += vec[i] * (pre[i-1] % mod) % mod;
    cout << ans % mod << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}