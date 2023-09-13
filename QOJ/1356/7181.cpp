#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

const int maxm = 100'000 + 5;

void solve() {
    int N, M; cin >> N >> M;
    
    vector ids(N+1, vector<int>());
    for (int i = 1; i <= M; ++i) {
        int u, v; cin >> u >> v;
        ids[u].eb(i), ids[v].eb(i);
    }
    
    vector<int> large(N+1, -1);
    vector<bitset<maxm>> large_eids;
    for (int i = 1, sq = int(ceil(sqrt(2*M))); i <= N; ++i) {
        if (SZ(ids[i]) >= sq) {
            large[i] = SZ(large_eids);
            bitset<maxm> eids;
            for (int x : ids[i]) eids[x] = 1;
            large_eids.eb(eids);
        }
    }
    
    int Q; cin >> Q;
    
    bitset<maxm> unused, alive;
    for (int i = 1; i <= M+1; ++i) unused[i] = 1;
    alive[M+1] = 1;
    
    for (int i = 0; i < Q; ++i) {
        char op; cin >> op;
        if (op == '?') {
            int pos = (alive & unused)._Find_first();
            if (pos == M+1) cout << 0 << "\n";
            else cout << pos << "\n", unused.reset(pos);
        }
        else if (op == '+' or op == '-') {
            int v; cin >> v;
            if (large[v] == -1) {for (int x : ids[v]) alive.flip(x);}
            else alive = alive ^ large_eids[large[v]];
        }
    }
}

int32_t main() {
    fastIO();
    
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
