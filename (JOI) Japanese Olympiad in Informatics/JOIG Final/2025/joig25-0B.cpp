#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

void solve() {
    int N, K; cin >> N >> K;
    
    vector grid(N+2, vector<int>(N+2, -1));
    for (int r = 1; r <= N; ++r) for (int c = 1; c <= N; ++c) cin >> grid[r][c];
    
    int base = 0;
    vector good(N+2, vector<int>(N+2, 0));
    for (int r = 1; r+1 <= N; ++r) for (int c = 1; c+1 <= N; ++c) {
        if (ssize(set<int>{grid[r][c], grid[r][c+1], grid[r+1][c], grid[r+1][c+1]}) >= 3) {
            good[r][c] = 1;
            ++base;
        }
    }
    
    int ans = base;
    for (int r = 1; r <= N; ++r) for (int c = 1; c <= N; ++c) for (int k = 1; k <= min<int>(K, 9); ++k) {
        int tmp = base - good[r-1][c-1] - good[r-1][c] - good[r][c-1] - good[r][c];
        if (ssize(set<int>{-1, grid[r-1][c-1], grid[r-1][c], grid[r][c-1], k}) >= 4) ++tmp;
        if (ssize(set<int>{-1, grid[r-1][c], grid[r-1][c+1], grid[r][c+1], k}) >= 4) ++tmp;
        if (ssize(set<int>{-1, grid[r][c-1], grid[r+1][c-1], grid[r+1][c], k}) >= 4) ++tmp;
        if (ssize(set<int>{-1, grid[r][c+1], grid[r+1][c], grid[r+1][c+1], k}) >= 4) ++tmp;
        chmax(ans, tmp);
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using i64 = long long;
#define int i64
using f64 = double;
using f80 = long double;
#define double f80
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

template <typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

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
#define fastIO() cin.tie(0)->sync_with_stdio(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

#endif
