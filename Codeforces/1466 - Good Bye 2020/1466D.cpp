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
    int n, sum = 0; cin >> n;
    
    vector<int> val(n), deg(n);
    for (auto &x : val) cin >> x, sum += x;
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v, --u, --v;
        ++deg[u], ++deg[v];
    }
    
    Prior<pii> pq;
    for (int i = 0; i < n; ++i) {
        if (deg[i] > 1) pq.push({val[i], deg[i]-1});
    }
    
    cout << sum << " ";
    while (!pq.empty()) {
        auto [_val, _id] = pq.top(); pq.pop();
        sum += _val;
        if (_id != 1) pq.push({_val, _id-1});
        cout << sum << " ";
    }
    cout << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}
