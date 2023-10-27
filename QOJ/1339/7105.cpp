#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

using p3i = tuple<int, int, int>;
using p4i = tuple<int, int, int, int>;

const vector<int> dx{1, 0, -1, 0};
const vector<int> dy{0, 1, 0, -1};

struct DSU {
    
    vector<int> p;
    int maxn, cc;
    
    void init(int N) {
        maxn = N + 1;
        p.resize(maxn), iota(ALL(p), 0);
        cc = 0;
    }
    
    int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
    int U(int x, int y) {x = R(x), y = R(y); return x ^ y ? p[x] = y, --cc, 1 : 0;}
    
    void add() {++cc;}
    
};

void solve() {
    int N, M, K; cin >> N >> M >> K;
    
    vector<p4i> lines(K);
    for (auto &[r1, c1, r2, c2] : lines) cin >> r1 >> c1 >> r2 >> c2;
    sort(ALL(lines));
    
    unordered_map<int, vector<p3i>> rows, cols;
    for (int i = 0; auto &[r1, c1, r2, c2] : lines) {
        if (r1 == r2) rows[r1].eb(c1, c2, i);
        else          cols[c1].eb(r1, r2, i);
        ++i;
    }
    for (auto &[r, row_vec] : rows) sort(ALL(row_vec));
    for (auto &[c, col_vec] : cols) sort(ALL(col_vec));
    
    auto search = [&](int r, int c) -> int {
        if (rows.contains(r)) {
            auto &row_vec = rows[r];
            auto it = lower_bound(ALL(row_vec), p3i{c+1, -1, -1});
            if (it != begin(row_vec) and get<1>(*prev(it)) >= c) return get<2>(*prev(it));
        }
        if (cols.contains(c)) {
            auto &col_vec = cols[c];
            auto it = lower_bound(ALL(col_vec), p3i{r+1, -1, -1});
            if (it != begin(col_vec) and get<1>(*prev(it)) >= r) return get<2>(*prev(it));
        }
        return -1;
    };
    
    vector<vector<pii>> ops(N+1);
    vector<int64_t> cnt(N+2, 0);
    for (int i = 0; auto &[r1, c1, r2, c2] : lines) {
        cnt[r1] += (c2 - c1 + 1), cnt[r2 + 1] -= (c2 - c1 + 1);
        for (int r, c; int d : {0, 1, 2, 3}) {
            r = r1 + dx[d], c = c1 + dy[d];
            if (int res = search(r, c); res != -1) ops[max(r1, r)].eb(i, res);
            r = r2 + dx[d], c = c2 + dy[d];
            if (int res = search(r, c); res != -1) ops[max(r2, r)].eb(i, res);
        }
        ++i;
    }
    partial_sum(ALL(cnt), begin(cnt));
    partial_sum(ALL(cnt), begin(cnt));
    
    DSU dsu; dsu.init(K);
    for (int r = 1, tok = 0; r <= N; ++r) {
        while (tok < K and get<0>(lines[tok]) == r) dsu.add(), ++tok;
        for (auto [a, b] : ops[r]) dsu.U(a, b);
        cout << cnt[r] << " " << dsu.cc << "\n";
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

// #define int int64_t
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

template <typename T, typename U>
ostream & operator << (ostream &os, const pair<T, U> &p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

#endif
