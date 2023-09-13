#include <bits/stdc++.h>
using namespace std;

#define int int64_t
using pii = pair<int, int>;

#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#endif

struct DSU {
    
    vector<int> p;
    int maxn;
    
    void init(int N) {
        maxn = N + 1;
        p.resize(maxn), iota(ALL(p), 0);
    }
    
    int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
    int U(int x, int y) {x = R(x), y = R(y); return x ^ y ? p[x] = y, 1 : 0;}
    
};

void solve() {
    int N, M; cin >> N >> M;
    
    vector<array<int, 5>> edges(M);
    for (int _id = 0; auto &[w, id, u, v, pick] : edges) cin >> u >> v >> w, id = _id++, pick = 0;
    sort(ALL(edges));
    
    DSU dsu; dsu.init(N);
    for (auto &[w, id, u, v, pick] : edges) pick = dsu.U(u, v);
    sort(ALL(edges), [](const auto &e1, const auto &e2) {return e1[1] < e2[1];});
    
    vector<pii> ops;
    for (int i = 0; i < N-1; ++i) {
        if (edges[i][4]) {edges[i][4] = 2; continue;}
        dsu.init(N);
        for (auto &[w, id, u, v, pick] : edges) {
            if ((i < id and id <= N-2) or pick == 2) dsu.U(u, v);
        }
        for (auto &[w, id, u, v, pick] : edges) {
            if (pick == 1 and dsu.U(u, v)) {pick = 2, ops.eb(i+1, id+1); break;}
        }
    }
    
    cout << SZ(ops) << "\n";
    for (auto [u, v] : ops) cout << u << " " << v << "\n";
}

int32_t main() {
    fastIO();
    
    solve();
    
    return 0;
}
