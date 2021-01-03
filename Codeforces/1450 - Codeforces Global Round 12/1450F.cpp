#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

void solve() {
    int n; cin >> n;
    
    int maxApp = 0;
    map<int, int> app;
    vector<int> v(n);
    for (auto &x : v) cin >> x, --x, maxApp = max(maxApp, ++app[x]);
    if (maxApp > (n+1) / 2) {cout << -1 << "\n"; return;}
    
    vector<vector<int>> seq(1);
    for (int i = 0; i < n; ++i) {
        if (i and v[i] == v[i-1]) seq.pb(vector<int>{v[i]});
        else seq.back().eb(v[i]);
    }
    
    // for (auto vec : seq) {
        // for (auto x : vec) cout << x << " ";
        // cout << "\n";
    // }
    
    int ans = seq.size() - 1;
    vector<int> cnt(n);
    Prior<pii> pq; /// (cnt[x], x)
    
    for (auto vec : seq) ++cnt[vec.front()], ++cnt[vec.back()];
    
    for (int i = 0; i < n; ++i) {
        if (cnt[i]) pq.push({cnt[i], i});
    }
    
    while (pq.size() > 1) {
        auto [cntA, A] = pq.top(); pq.pop();
        auto [cntB, B] = pq.top(); pq.pop();
        if (cntA > 1) pq.push({cntA - 1, A});
        if (cntB > 1) pq.push({cntB - 1, B});
    }
    if (!pq.empty()) ans += pq.top().X / 2 - 1;
    
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}
