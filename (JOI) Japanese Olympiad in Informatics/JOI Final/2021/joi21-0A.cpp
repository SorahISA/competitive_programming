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

const int INF = 1E15;

void solve() {
    int n; cin >> n;
    
    vector<int> h(n);
    for (auto &x : h) cin >> x;
    
    vector<int> lans(n), rans(n);
    for (int l = 1, r = n-2; l < n; ++l, --r) {
        lans[l] = lans[l-1] + (h[l] > h[l-1] ? 0LL : h[l-1] - h[l] + 1);
        rans[r] = rans[r+1] + (h[r] > h[r+1] ? 0LL : h[r+1] - h[r] + 1);
    }
    
    int ans = INF;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, max(lans[i], rans[i]));
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}