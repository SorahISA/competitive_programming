#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

void solve() {
    int N, M; cin >> N >> M;
    
    vector<int> deg(N);
    for (int i = 0, u, v; i < M; ++i) cin >> u >> v, --u, --v, ++deg[u], ++deg[v];
    sort(RALL(deg));
    
    int clique = 0;
    for (int i = N-1; i >= 0; --i) {
        if (deg[i] >= i) {clique = i+1; break;}
    }
    
    int ans_clique = 1;
    for (int i = clique; i < N; ++i) {
        if (deg[i] == clique-1) ++ans_clique;
    }
    
    int ans_independent;
    if (deg[clique-1] == clique-1) {
        ans_independent = 0;
        for (int i = clique-1; i >= 0; --i) {
            if (deg[i] == clique-1) ++ans_independent;
        }
    }
    else if (deg[clique-1] == clique) {
        ans_independent = 1;
        for (int i = clique-1; i >= 0; --i) {
            if (deg[i] == clique) ++ans_independent;
        }
    }
    else {
        ans_independent = 1;
    }
    
    cout << ans_clique << " " << ans_independent << "\n";
    // debug(ans_clique, ans_independent);
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
