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

const int maxn = 1E5 + 5;

int ans = 0;
vector<int> adj[maxn];

void dfs(int now, int lst) {
    int child = adj[now].size() - (now != lst);
    if (child) ans += __lg(child) + 1 + child;
    for (auto x : adj[now]) {
        if (x != lst) dfs(x, now);
    }
}

void solve() {
    int n; cin >> n;
    
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].eb(v), adj[v].eb(u);
    }
    
    dfs(1, 1);
    
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
