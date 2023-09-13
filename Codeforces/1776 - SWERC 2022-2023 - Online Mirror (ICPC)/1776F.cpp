#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80
using pii = pair<int, int>;
template <typename T> using MaxHeap = std::priority_queue<T>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;

template <size_t D, typename T> struct Vec : vector<Vec<D-1, T>> {
    template <typename ...U> Vec(int n = 0, U ..._u) :
        vector<Vec<D-1, T>>(n, Vec<D-1, T>(_u...)) {}
};

template <typename T> struct Vec<1, T> : vector<T> {
    Vec(int n = 0, const T &val = T()) :
        vector<T>(n, val) {}
};

// #define X first
// #define Y second
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
#define SZ(x) ((int)(x).size())
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\e[1;93mAt [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), fprintf(stderr, "\e[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define endl "\n"
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N, M; cin >> N >> M;
    
    vector<int> deg(N, 0);
    vector<pii> edges(M);
    for (auto &[u, v] : edges) cin >> u >> v, ++deg[--u], ++deg[--v];
    
    if (M == N*(N-1)/2) {
        cout << 3 << "\n";
        int a = 1, b = 2;
        for (auto [u, v] : edges) {
                 if (u != a and v != a) cout << 1 << " ";
            else if (u == b or  v == b) cout << 2 << " ";
            else                        cout << 3 << " ";
        }
        cout << "\n";
    }
    else {
        cout << 2 << "\n";
        int a = min_element(ALL(deg)) - begin(deg);
        for (auto [u, v] : edges) {
            if (u != a and v != a) cout << 1 << " ";
            else                   cout << 2 << " ";
        }
        cout << "\n";
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
