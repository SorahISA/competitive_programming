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

const int INF = 1000;
const int maxn = 200 + 5;

int fl = 1;
vector<int> adj[maxn], vis(maxn);

void dfs_bipartite(int now) {
    for (auto x : adj[now]) {
        if (vis[x] == 0) vis[x] = vis[now] ^ 1, dfs_bipartite(x);
        else if (vis[x] != vis[now] ^ 1) fl = 0;
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> dis(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) dis[i][i] = 0;
    for (int i = 0; i < m; ++i) {
        int u, v, w; cin >> u >> v >> w, --u, --v;
        dis[u][v] = 1, dis[v][u] = w ? -1 : 1;
        adj[u].eb(v), adj[v].eb(u);
    }
    
    vis[1] = 2, dfs_bipartite(1);
    
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
                if (dis[i][j] <= -n) fl = 0;
            }
        }
    }
    
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dis[i][j] > dis[i][k] + dis[k][j]) fl = 0;
            }
        }
    }
    
    int ans = 0, ansID = 0;
    for (int i = 0; i < n; ++i) {
        if (*max_element(ALL(dis[i])) - *min_element(ALL(dis[i])) > ans) {
            ans = *max_element(ALL(dis[i])) - *min_element(ALL(dis[i]));
            ansID = i;
        }
    }
    
    if (fl) {
        cout << "YES\n";
        cout << ans << "\n";
        for (int i = 0; i < n; ++i) cout << 1000 + dis[ansID][i] << " \n"[i == n-1];
    }
    else {
        cout << "NO\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
