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
#define ef push_front
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int maxn = 2E5 + 5;

vector<pii> adj[maxn], par(maxn);
vector<int> dep(maxn), p(maxn);

void dfs(int now, int lst = -1) {
    for (auto [x, val] : adj[now]) {
        if (x == lst) continue;
        par[x] = {now, val}, dep[x] = dep[now] + 1;
        dfs(x, now);
    }
}

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}

void U(int x, int y) {
    x = R(x), y = R(y);
    if (dep[x] < dep[y]) swap(x, y);
    p[x] = y;
}

void solve() {
    int N, Q; cin >> N >> Q;
    iota(ALL(p), 0);
    
    for (int i = 0; i < N-1; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].eb(v, w), adj[v].eb(u, w);
    }
    dfs(1);
    
    while (Q--) {
        int ans = 0, u, v; cin >> u >> v;
        while (u != v) {
            if (dep[u] < dep[v]) swap(u, v);
            ans += par[u].Y, par[u].Y = 0;
            U(u, par[u].X), u = R(u);
        }
        cout << ans << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}
