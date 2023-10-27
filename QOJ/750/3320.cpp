#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

const int max_color = 100'000 + 5;

struct LCA {
    
    vector<vector<int>> anc;
    vector<int> dep;
    int lgmx, maxn;
    
    void init(int N) {
        maxn = (1 << (__lg(N+1) + 1));
        lgmx = __lg(maxn);
        anc.assign(lgmx, vector<int>(maxn, 0));
        dep.assign(maxn, 0);
    }
    
    void set(vector<int> &p, vector<int> &d) {
        for (int i = 0; i < SZ(p); ++i) anc[0][i] = p[i];
        dep = d;
    }
    
    void build() {
        for (int lay = 1; lay < lgmx; ++lay) {
            for (int i = 0; i < maxn; ++i) {
                anc[lay][i] = anc[lay-1][anc[lay-1][i]];
            }
        }
    }
    
    int lca(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        for (int lay = lgmx-1, dif = dep[u] - dep[v]; lay >= 0; --lay) {
            if (dif >> lay & 1) u = anc[lay][u];
        }
        if (u == v) return u;
        for (int lay = lgmx-1; lay >= 0; --lay) {
            if (anc[lay][u] != anc[lay][v]) u = anc[lay][u], v = anc[lay][v];
        }
        return anc[0][u];
    }
    
    int dis(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    
};

void dfs(auto &adj, auto &dep, auto &par, auto &dfn, int &tok, int now, int lst) {
    par[now] = lst, dfn[now] = tok++;
    for (int x : adj[now]) {
        if (x == lst) continue;
        dep[x] = dep[now] + 1;
        dfs(adj, dep, par, dfn, tok, x, now);
    }
}

void solve() {
    int N; cin >> N;
    
    Vec<2, int> adj(N);
    for (int i = 0, a, b; i < N-1; ++i) {
        cin >> a >> b, --a, --b;
        adj[a].eb(b), adj[b].eb(a);
    }
    
    /// init tree ///
    
    vector<int> dep(N, 0), par(N, 0), dfn(N, 0);
    int dfn_tok = 0;
    dfs(adj, dep, par, dfn, dfn_tok, 0, 0);
    
    /// a -> dfn[a] ///
    
    vector<int> dep2(N, 0), par2(N, 0);
    for (int i = 0; i < N; ++i) {
        dep2[dfn[i]] = dep[i];
        par2[dfn[i]] = dfn[par[i]];
    }
    
    /// input color using dfn[] ///
    
    vector<int> C(N);
    for (int i = 0; i < N; ++i) cin >> C[dfn[i]];
    
    /// init answer for each color ///
    
    LCA meow;
    meow.init(N);
    meow.set(par2, dep2);
    meow.build();
    
    vector<set<int>> color(max_color);
    vector<int> ans(max_color, 0); /// tree edges * 2
    for (int i = 0; i < N; ++i) color[C[i]].ee(i);
    for (int c = 0; c < max_color; ++c) {
        if (SZ(color[c]) == 0) {ans[c] = 0; continue;}
        int lst = *rbegin(color[c]);
        for (int x : color[c]) {
            ans[c] += meow.dis(x, lst);
            lst = x;
        }
    }
    
    /// query ///
    
    int M; cin >> M;
    
    for (int q = 1; q <= M; ++q) {
        char op; cin >> op;
        
        if (op == 'U') {
            int x, y; cin >> x >> y, x = dfn[x-1];
            
            /// remove x from C[x] ///
            {
                auto it = color[C[x]].find(x);
                int lst = (it == begin(color[C[x]]) ? *rbegin(color[C[x]]) : *prev(it));
                int now = *it;
                int nxt = (it == prev(end(color[C[x]])) ? *begin(color[C[x]]) : *next(it));
                
                ans[C[x]] -= meow.dis(lst, now);
                ans[C[x]] -= meow.dis(now, nxt);
                ans[C[x]] += meow.dis(lst, nxt);
            }
            
            color[C[x]].erase(x);
            C[x] = y;
            color[C[x]].ee(x);
            
            /// add y to C[y] ///
            {
                auto it = color[C[x]].find(x);
                int lst = (it == begin(color[C[x]]) ? *rbegin(color[C[x]]) : *prev(it));
                int now = *it;
                int nxt = (it == prev(end(color[C[x]])) ? *begin(color[C[x]]) : *next(it));
                
                ans[C[x]] += meow.dis(lst, now);
                ans[C[x]] += meow.dis(now, nxt);
                ans[C[x]] -= meow.dis(lst, nxt);
            }
        }
        else if (op == 'Q') {
            int y; cin >> y;
            cout << (SZ(color[y]) == 0 ? -1 : ans[y] / 2) << "\n";
        }
    }
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize ("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int int64_t
// #define double __float80
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) ((int)(a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
// #define X first
// #define Y second

template <size_t D, typename T> struct Vec : vector<Vec<D-1, T>> {
    template <typename... U> Vec(int n = 0, U ... _u) : vector<Vec<D-1, T>>(n, Vec<D-1, T>(_u...)) {}
};
template <typename T> struct Vec<1, T> : vector<T> {
    Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
};

#ifdef local
#define IOS() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << endl;}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#define debug(...) void()
#define endl '\n'
#endif

template <typename U, typename V> bool chmin(U &u, V v) {return u > v ? u = v, 1 : 0;}
template <typename U, typename V> bool chmax(U &u, V v) {return u < v ? u = v, 1 : 0;}

#endif
