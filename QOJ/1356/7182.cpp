#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

using p3i = tuple<int, int, int>;

const int maxn = (1 << 16) + 5;
// int max_depth = 0;

vector<int> sq(maxn);

void recur(auto &edges, int L, int R, bool output = false, int dep = 1) {
    // if (chmax(max_depth, dep)) debug(dep);
    
    int B = sq[R-L];
    vector<int> big;
    for (int i = L; i < R; i += B) big.eb(i);
    big.eb(R);
    
    if (output) {
        // if (chmax(max_depth, dep)) debug(dep, L, R, 2*(R-L-2));
        for (int i = L+2; i <= R-1; ++i) edges.eb(L, i-1, i);
        for (int i = R-2; i >= L+1; --i) edges.eb(i, i+1, R);
    }
    
    if (R - L <= 2) return;
    
    for (int i = 0; i+1 < SZ(big); ++i) recur(edges, big[i], big[i+1], true, dep+1);
    
    // for (int id = 0; id+1 < SZ(big); ++id) {
    //     int i = big[id], b = big[id+1] - big[id];
    //     /// link i to i+1, ..., i+B-1 ///
    //     /// link i+1, ..., i+B-1 to i+B ///
    //     /// link i to i+B ///
    //     for (int j = 2; j <= b-1; ++j) edges.eb(i, i+j-1, i+j);
    //     for (int j = b-2; j >= 1; --j) edges.eb(i+j, i+j+1, i+b);
    //     if (b != 1) edges.eb(i, i+1, i+b);
    // }
    
    for (int i = 0; i+1 < SZ(big); ++i) edges.eb(big[i], big[i]+1, big[i+1]);
    for (int len = 2; len < SZ(big); ++len) {
        for (int i = 0, j = i+len; j < SZ(big); ++i, ++j) edges.eb(big[i], big[i+1], big[j]);
    }
}

pii query(int L, int R, int u, int v) {
    int B = sq[R-L];
    int u_blk = (u - L) / B * B + L, v_blk = (v - L) / B * B + L;
    
    if (u_blk == v_blk) return query(u_blk, min(u_blk + B, R), u, v);
    return {min(u_blk + B, R), v_blk};
}

void solve() {
    int N; cin >> N;
    
    vector<p3i> _edges;
    recur(_edges, 0, N);
    
    set<pii> edge_set;
    vector<p3i> edges;
    for (int i = 0; i+1 <= N; ++i) edge_set.ee(i, i+1);
    for (auto [a, b, c] : _edges) {
        if (edge_set.contains(pii{a, c})) continue;
        edge_set.ee(a, c);
        edges.eb(a, b, c);
        if (a == b or b == c or a == c) {
            // debug(a, b, c);
            assert(false);
        }
        if (!edge_set.contains(pii{a, b}) or !edge_set.contains(pii{b, c})) {
            // debug("add", a, c, "no", a, b, "or", b, c);
            assert(false);
        }
    }
    
    // assert(SZ(edges) <= 6 * N); /// not here
    
    cout << SZ(edges) << "\n";
    for (auto [a, b, c] : edges) cout << a << " " << b << " " << c << "\n";
    cout << flush;
    
    /// start query ///
    
    int Q; cin >> Q;
    
    for (int q = 1; q <= Q; ++q) {
        int l, r; cin >> l >> r;
        // l = rng() % (N+1), r = (l + rng() % N) % (N+1);
        // if (l > r) swap(l, r);
        
        if (r - l <= 3) {
            for (int i = l; i <= r; ++i) cout << i << " \n"[i == r];
            cout << flush;
            continue;
        }
        
        pii res = query(0, N, l, r);
        vector<int> ans{l, res.first, res.second, r};
        ans.erase(unique(ALL(ans)), end(ans));
        
        for (int i = 0; i < SZ(ans); ++i) cout << ans[i] << " \n"[i == SZ(ans)-1];
        cout << flush;
        
        for (int i = 0; i+1 < SZ(ans); ++i) {
            if (!edge_set.contains(pii{ans[i], ans[i+1]})) {
                // debug(ans);
                assert(false);
            }
        }
    }
    
}

void init() {
    for (int i = 0; i < maxn; ++i) {
        // sq[i] = int(sqrt(i));
             if (i <= (1 <<  1)) sq[i] = (1 << 0);
        else if (i <= (1 <<  2)) sq[i] = (1 << 1);
        else if (i <= (1 <<  4)) sq[i] = (1 << 2);
        else if (i <= (1 <<  8)) sq[i] = (1 << 4);
        else if (i <= (1 << 16)) sq[i] = (1 << 8);
    }
}

int32_t main() {
    fastIO();
    init();
    
    int t = 1; // cin >> t;
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
