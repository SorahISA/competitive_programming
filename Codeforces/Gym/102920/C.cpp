#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define pb push_back
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

const int maxn = 1E5 + 5;
const int lgmx = 18 + 1;

vector<int> adj[maxn], dep(maxn, 0), dfn(maxn, 0);
int anc[maxn][lgmx], tok = 0;

void dfs(int now, int lst) {
    anc[now][0] = lst == -1 ? now : lst;
    dep[now] = lst == -1 ? 0LL : dep[lst] + 1;
    dfn[now] = ++tok;
    for (auto x : adj[now]) {
        if (x != lst) dfs(x, now);
    }
}

void build(int n) {
    for (int lay = 1; lay < lgmx; ++lay) {
        for (int i = 1; i <= n; ++i) {
            anc[i][lay] = anc[anc[i][lay-1]][lay-1];
        }
    }
}

int lca(int u, int v) {
    if (dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for (int i = 0; i < lgmx; ++i) {
        if (diff >> i & 1) u = anc[u][i];
    }
    if (u == v) return u;
    for (int i = lgmx-1; i >= 0; --i) {
        if (anc[u][i] != anc[v][i]) {
            u = anc[u][i], v = anc[v][i];
        }
    }
    return anc[u][0];
}

void solve() {
    int n, k; cin >> n >> k;
    
    for (int i = 0; i < n-1; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].eb(v), adj[v].eb(u);
    }
    vector<int> apartment(k);
    for (auto &x : apartment) cin >> x;
    
    dfs(1, -1), build(n);
    sort(ALL(apartment), [](auto a1, auto a2) {
        return dfn[a1] < dfn[a2];
    });
    
    // for (int i = 1; i <= n; ++i) cout << dep[i] << " \n"[i == n];
    
    int mst_weight = 0;
    for (int i = 0; i < k; ++i) {
        int _lca = lca(apartment[i], apartment[(i+1)%k]);
        mst_weight += dep[apartment[i]] - dep[_lca];
    }
    cout << mst_weight + 1 << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}