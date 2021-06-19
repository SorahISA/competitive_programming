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

template<typename T>
ostream &operator << (ostream &os, const vector<T> &v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i) os << "\n";
        os << v[i];
    }
    return os;
}

const int maxn = 2E5 + 5;

vector<int> adj[maxn], dep(maxn, 0), sz(maxn, 1), cnt(maxn, 0), ans;
vector<pii> qry[maxn]; /// (d, id)

void dfs_sz(int now) {
    for (auto x : adj[now]) {
        dfs_sz(x), sz[now] += sz[x];
    }
    sort(ALL(adj[now]), [](int x, int y) {return sz[x] > sz[y];});
}

void dfs_del(int now) {
    // cout << "del " << now << "\n";
    --cnt[dep[now]];
    for (auto x : adj[now]) dfs_del(x);
}

void dfs(int now, int calc, int bring) {
    int heavy = adj[now].empty() ? (int)0 : adj[now].front();
    for (auto x : adj[now]) if (x != heavy) dfs(x, calc&1, 0);
    if (heavy) dfs(heavy, calc&1, 1);
    for (auto x : adj[now]) if (x != heavy) dfs(x, 0, 1);
    ++cnt[dep[now]];
    // cout << now << ": "; for (int i = 0; i <= 5; ++i) cout << cnt[i] << " \n"[i == 5];
    if (calc) for (auto [d, id] : qry[now]) ans[id] += dep[now] > d ? (int)0 : cnt[d];
    if (!bring) dfs_del(now);
}

void solve() {
    int N; cin >> N;
    for (int i = 2, par; i <= N; ++i) cin >> par, adj[par].eb(i), dep[i] = dep[par] + 1;
    
    int Q; cin >> Q, ans.assign(Q, 0);
    for (int i = 0, u, d; i < Q; ++i) cin >> u >> d, qry[u].eb(d, i);
    
    dfs_sz(1), dfs(1, 1, 1);
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