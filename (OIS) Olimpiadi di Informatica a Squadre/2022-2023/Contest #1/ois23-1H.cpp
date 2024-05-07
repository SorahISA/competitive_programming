#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

template <size_t D, typename T> struct Vec : vector<Vec<D-1, T>> {
    template <typename ...U> Vec(int n = 0, U ..._u) :
        vector<Vec<D-1, T>>(n, Vec<D-1, T>(_u...)) {}
};

template <typename T> struct Vec<1, T> : vector<T> {
    Vec(int n = 0, const T &val = T()) :
        vector<T>(n, val) {}
};

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << endl;}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#define endl "\n"
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N, R, T; cin >> N >> R >> T;
    
    int sum = 0, thres = N * (R + T);
    for (int i = 0, s_i; i < N; ++i) cin >> s_i, sum += s_i;
    
    if (sum > thres) cout << "Cheater" << "\n";
    else             cout << "Innocent" << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
