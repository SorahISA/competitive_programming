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

const int maxn = 1E5 + 5;

vector<int> val[maxn], ans(maxn, -1), p(maxn);
vector<pii> ops, pl;

int R(int x) {return x ^ p[x] ? R(p[x]) : x;}

void U(int x, int y, int id) {
    x = R(x), y = R(y);
    // cerr << "merge " << x << " " << y << "\n";
    if (x == y) return;
    if (SZ(val[x]) > SZ(val[y])) swap(x, y);
    p[x] = y;
    for (int z : val[x]) {
        if (pl[z].X == y or pl[z].Y == y) ans[z] = id;
        else (pl[z].X == x ? pl[z].X : pl[z].Y) = y, val[y].eb(z);
    }
    vector<int>().swap(val[x]);
}

void solve() {
    iota(ALL(p), 0);
    
    int N, M; cin >> N >> M, ops.resize(M);
    
    for (auto &[u, v] : ops) cin >> u >> v;
    
    int Q; cin >> Q, pl.resize(Q);
    
    for (int tok = 0; auto &[u, v] : pl) cin >> u >> v, val[u].eb(tok), val[v].eb(tok), ++tok;
    
    for (int tok = 0; auto [u, v] : ops) U(u, v, ++tok);
    
    for (int i = 0; i < Q; ++i) cout << ans[i] << "\n";
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
