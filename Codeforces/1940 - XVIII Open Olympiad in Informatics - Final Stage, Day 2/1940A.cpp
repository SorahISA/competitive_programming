#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

struct DSU {
    
    vector<int> p;
    int maxn;
    
    void init(int N) {
        maxn = N + 1;
        p.resize(maxn), iota(ALL(p), 0);
    }
    
    int R(int x) { return x ^ p[x] ? p[x] = R(p[x]) : x; }
    int U(int x, int y) { return (x = R(x)) ^ (y = R(y)) ? p[x] = y, 1 : 0; }
    
};

void solve() {
    int N, M1, M2; cin >> N >> M1 >> M2;
    
    set<pii> edges1, edges2;
    for (int i = 0; i < M1; ++i) {
        int u, v; cin >> u >> v, --u, --v;
        edges1.ee(min(u, v), max(u, v));
    }
    for (int i = 0; i < M2; ++i) {
        int a, b; cin >> a >> b, --a, --b;
        edges2.ee(min(a, b), max(a, b));
    }
    
    if (N == 3) {
        vector adj(3, vector<int>(3, 0));
        for (auto [u, v] : edges1) adj[u][v] ^= 1, adj[v][u] ^= 1;
        for (auto [a, b] : edges2) adj[a][b] ^= 2, adj[b][a] ^= 2;
        if (M1 + M2 == 3 and adj[0][1] and adj[0][2] and adj[1][2]) cout << "No" << "\n";
        else {
            vector<pii> ans;
            if (~adj[0][1] >> 1 & 1) ans.eb(0, 1), adj[0][1] ^= 3, adj[1][0] ^= 3;
            if (~adj[0][2] >> 1 & 1) ans.eb(0, 2), adj[0][2] ^= 3, adj[2][0] ^= 3;
            if (~adj[1][2] >> 1 & 1) ans.eb(1, 2), adj[1][2] ^= 3, adj[2][1] ^= 3;
            int flag = 0;
            if (!flag and (~adj[0][1] >> 0 & 1)) ans.eb(0, 1), adj[0][1] ^= 3, adj[1][0] ^= 3, flag = 1;
            if (!flag and (~adj[0][2] >> 0 & 1)) ans.eb(0, 2), adj[0][2] ^= 3, adj[2][0] ^= 3, flag = 1;
            if (!flag and (~adj[1][2] >> 0 & 1)) ans.eb(1, 2), adj[1][2] ^= 3, adj[2][1] ^= 3, flag = 1;
            
            cout << "Yes" << "\n";
            cout << SZ(ans) << "\n";
            for (auto [u, v] : ans) cout << u + 1 << " " << v + 1 << "\n";
        }
        return;
    }
    
    vector<pii> ans;
    
    /// find MST with maxdeg < N-1 on G2, add one edge if needed, call it T2 ///
    /// find MST on Kn - T2, call it T1 ///
    
    DSU dsu; dsu.init(N);
    set<pii> T2;
    vector<int> deg(N, 0);
    for (auto [x, y] : edges2) {
        if (dsu.U(x, y)) T2.ee(x, y), ++deg[x], ++deg[y];
    }
    // assert(SZ(T2) == N-1);
    
    if (auto it = find(ALL(deg), N-1); it != end(deg)) {
        // debug(":(");
        int max_pos = it - begin(deg);
        auto make_exist_T2 = [&](int x, int y) {
            if (x > y) swap(x, y);
            if (!edges2.contains({x, y})) {
                if (auto _it = edges1.find({x, y}); _it != end(edges1)) edges1.erase(_it), --M1;
                else edges1.ee(x, y), ++M1;
                if (auto _it = edges2.find({x, y}); _it != end(edges2)) edges2.erase(_it), --M2;
                else edges2.ee(x, y), ++M2;
                /// remove (max_pos, x); link (x, y) ///
                T2.erase({min(max_pos, x), max(max_pos, x)}), --deg[max_pos], --deg[x];
                T2.ee(x, y), ++deg[x], ++deg[y], ans.eb(x, y);
            }
            else {
                /// remove (max_pos, x); link (x, y) ///
                T2.erase({min(max_pos, x), max(max_pos, x)}), --deg[max_pos], --deg[x];
                T2.ee(x, y), ++deg[x], ++deg[y];
            }
        };
        if (max_pos >= 2) make_exist_T2(0, 1);
        else              make_exist_T2(2, 3);
    }
    // assert(SZ(T2) == N-1);
    // assert(!count(ALL(deg), N-1));
    
    set<pii> T1;
    set<int> unvisited;
    for (int i = 1; i < N; ++i) unvisited.ee(i);
    deque<int> deq{0};
    while (SZ(deq)) {
        int now = deq[0]; deq.pf();
        int tok = SZ(deq);
        for (int x : unvisited) {
            if (!T2.contains({min(now, x), max(now, x)})) T1.ee(min(now, x), max(now, x)), deq.eb(x);
        }
        while (tok < SZ(deq)) unvisited.erase(deq[tok++]);
    }
    // assert(SZ(T1) == N-1);
    
    // for (auto [u, v] : edges1) debug(u, v);
    // for (auto [u, v] : T1) debug(u, v);
    
    dsu.init(N);
    for (auto [u, v] : edges1) dsu.U(u, v);
    for (auto [u, v] : T1) { if (dsu.U(u, v)) ans.eb(u, v); }
    
    cout << "Yes" << "\n";
    cout << SZ(ans) << "\n";
    for (auto [u, v] : ans) cout << u + 1 << " " << v + 1 << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1, g; cin >> t >> g;
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

using i64 = long long;
#define int i64
using f80 = long double;
#define double f80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define eb emplace_back
#define pb pop_back
#define ef emplace_front
#define pf pop_front
#define ee emplace
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) { cerr << _t << "\n"; }
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) { cerr << _t << ", ", _do(_u...); }
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

#endif
