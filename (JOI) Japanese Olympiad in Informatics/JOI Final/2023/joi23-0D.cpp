#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int lgmx = 18;
const int maxn = 1 << lgmx;

vector<vector<int>> adj;

namespace LCA {

vector<vector<int>> anc(lgmx, vector<int>(maxn));
vector<int> dep;

void dfs(int now, int par = 0) {
    anc[0][now] = par;
    for (int x : adj[now]) {
        if (x != par) dep[x] = dep[now] + 1, dfs(x, now);
    }
}

void build(int N) {
    dep.assign(N, 0), dfs(0);
    for (int lay = 1; lay < lgmx; ++lay) {
        for (int i = 0; i < N; ++i) anc[lay][i] = anc[lay-1][ anc[lay-1][i] ];
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    for (int diff = dep[x] - dep[y], lay = lgmx-1; lay >= 0; --lay) {
        if (diff >> lay & 1) x = anc[lay][x];
    }
    if (x == y) return x;
    for (int lay = lgmx-1; lay >= 0; --lay) {
        if (anc[lay][x] != anc[lay][y]) x = anc[lay][x], y = anc[lay][y];
    }
    return anc[0][x];
}

int get_dis(int x, int y) {
    int z = lca(x, y);
    return dep[x] + dep[y] - 2 * dep[z];
}

}

namespace DSU {

vector<int> p, mx;

void init(int N) {
    p.resize(N), iota(ALL(p), 0);
    mx.resize(N), iota(ALL(mx), 0);
}

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
int U(int x, int y) {x = R(x), y = R(y); return x ^ y ? chmax(mx[y], mx[x]), p[x] = y, 1 : 0;}

int get_max(int x) {return mx[R(x)];}

}

void solve() {
    int N; cin >> N;
    
    vector<int> P(N);
    for (int &x : P) cin >> x, --x;
    
    adj.resize(N);
    vector<pii> edges(N-1);
    for (auto &[u, v] : edges) {
        cin >> u >> v, --u, --v, adj[P[u]].eb(P[v]), adj[P[v]].eb(P[u]);
        // debug(P[u], P[v]);
    }
    
    LCA::build(N), DSU::init(N);
    
    vector<int> dp(N, 0);
    for (int i = 0; i < N; ++i) {
        for (int x : adj[i]) {
            if (x > i) continue;
            int big = DSU::get_max(x);
            chmax(dp[i], dp[big] + LCA::get_dis(i, big));
            DSU::U(i, big);
            // debug(i, x, big, dp[big]);
        }
        // debug(i, dp[i]);
    }
    cout << dp.back() << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
