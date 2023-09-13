#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

struct LCA {
    
    vector<vector<int>> anc;
    vector<int> dep;
    int lgmx, maxn;
    
    void init(int N, vector<int> &par, vector<int> &_dep) {
        lgmx = __lg(N+1) + 1;
        maxn = N + 1;
        anc.assign(lgmx, vector<int>(maxn, 0));
        anc[0] = par, anc[0].resize(maxn, 0);
        dep = _dep, dep.resize(maxn, 0);
    }
    
    void build() {
        for (int lay = 1; lay < lgmx; ++lay) {
            for (int i = 0; i < maxn; ++i) {
                anc[lay][i] = anc[lay-1][ anc[lay-1][i] ];
            }
        }
    }
    
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int lay = lgmx-1; lay >= 0; --lay) {
            if ((dep[u] - dep[v]) >> lay & 1) u = anc[lay][u];
        }
        if (u == v) return u;
        for (int lay = lgmx-1; lay >= 0; --lay) {
            if (anc[lay][u] != anc[lay][v]) u = anc[lay][u], v = anc[lay][v];
        }
        return anc[0][u];
    }
    
};

void dfs_init(auto &adj, auto &vis, auto &rt, auto &red, auto &par, auto &dep, auto &dep1, int now) {
    vis[now] = 1;
    for (auto [x, dis] : adj[now]) {
        if (vis[x]) continue;
        par[x] = now;
        dep[x] = (red[x] ? 0 : dep[now] + dis);
        dep1[x] = dep1[now] + 1;
        rt[x] = (red[x] ? x : rt[now]);
        dfs_init(adj, vis, rt, red, par, dep, dep1, x);
    }
}

void solve() {
    int N, M, Q; cin >> N >> M >> Q;
    
    vector<int> red(N+1, 0);
    for (int i = 0, r; i < M; ++i) cin >> r, red[r] = 1;
    
    vector<vector<pii>> adj(N+1);
    for (int i = 0; i < N-1; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].eb(v, w), adj[v].eb(u, w);
    }
    
    vector<int> vis(N+1, 0), rt(N+1, 0), par(N+1, 0), dep(N+1, 0), dep1(N+1, 0);
    rt[1] = 1;
    dfs_init(adj, vis, rt, red, par, dep, dep1, 1);
    
    // debug(vis);
    // debug(rt);
    // debug(par);
    // debug(dep);
    
    LCA tree;
    tree.init(N, par, dep1);
    tree.build();
    
    for (int q = 1; q <= Q; ++q) {
        int K; cin >> K;
        
        vector<int> V(K);
        for (int &x : V) cin >> x;
        sort(ALL(V), [&](int x, int y) {
            if (rt[x] != rt[y]) return rt[x] < rt[y];
            return dep[x] > dep[y];
        });
        // debug(V);
        
        int mx1 = 0, mx2 = 0;
        for (int i = 0, j; i < K; i = j) {
            int max_dep = dep[V[i]];
            for (j = i+1; j < K and rt[V[j]] == rt[V[i]]; ++j) {
                chmax(max_dep, dep[V[j]]);
            }
            int sec_dep = max_dep;
            for (int p = i, a = V[i]; p < j; ++p) {
                a = tree.lca(a, V[p]);
                chmin(sec_dep, max(dep[V[i]] - dep[a], (p+1 < j ? dep[V[p+1]] : 0)));
            }
            if (max_dep > mx1) swap(mx1, max_dep);
            if (max_dep > mx2) swap(mx2, max_dep);
            if (sec_dep > mx1) swap(mx1, sec_dep);
            if (sec_dep > mx2) swap(mx2, sec_dep);
            // debug(i, j, max_dep, sec_dep);
        }
        cout << mx2 << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
// #define double __float80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "%sAt [%s], line %d: (%s) = ", "\u001b[33m", __FILE__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), fprintf(stderr, "%s", "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

template <typename T>
ostream & operator << (ostream &os, const vector<T> &vec) {
    os << "[";
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << ", ";
        os << vec[i];
    }
    os << "]";
    return os;
}

#endif
