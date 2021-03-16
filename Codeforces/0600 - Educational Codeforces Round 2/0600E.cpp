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

template<class T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxn = 1E5 + 5;

int maxC = 0;
vector<int> adj[maxn], sz(maxn), heavy(maxn);
vector<int> col(maxn), vis(maxn), cnt(maxn), sumC(maxn), ans(maxn);

void hld(int now, int lst) {
    /// get size of subtree and heavy child ///
    sz[now] = 1, heavy[now] = -1;
    int maxSZ = -1;
    for (auto x : adj[now]) {
        if (x == lst) continue;
        hld(x, now), sz[now] += sz[x];
        if (sz[x] > maxSZ) maxSZ = sz[x], heavy[now] = x;
    }
}

void update(int now, int lst, int val) {
    /// update answer, dsu-on-tree varies here ///
    if (val ==  1 and cnt[col[now]] == maxC) ++maxC;
    if (val == -1 and cnt[col[now]] == maxC and col[now] == sumC[maxC]) --maxC;
    sumC[cnt[col[now]]] -= col[now], cnt[col[now]] += val, sumC[cnt[col[now]]] += col[now];
    
    /// update using brute force ///
    for (auto x : adj[now]) {
        if (x == lst or vis[x]) continue;
        update(x, now, val);
    }
}

void dfs(int now, int lst, int keep) {
    /// dfs to each non-heavy child and calculate its contribution ///
    /// cnt[] should be all 0 at this time ///
    for (auto x : adj[now]) {
        if (x == lst or x == heavy[now]) continue;
        dfs(x, now, 0);
    }
    
    /// visit the heavy child and keep the contribution ///
    /// vis[heavy[now]] = 1/0 is for update() not going into the heavy child ///
    /// visit the non-heavy child and count their contribution ///
    if (heavy[now] != -1) dfs(heavy[now], now, 1), vis[heavy[now]] = 1;
    update(now, lst, 1);
    if (heavy[now] != -1) vis[heavy[now]] = 0;
    
    /// get answer ///
    ans[now] = sumC[maxC];
    
    /// delete the contribution of subtree[now] ///
    if (!keep) update(now, lst, -1);
}

void solve() {
    int n; cin >> n;
    
    for (int i = 1; i <= n; ++i) cin >> col[i];
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].eb(v), adj[v].eb(u);
    }
    
    hld(1, -1), dfs(1, -1, 1);
    
    for (int i = 1; i <= n; ++i) cout << ans[i] << " \n"[i == n];
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}