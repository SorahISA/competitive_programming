#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

void solve() {
    int N; cin >> N;
    
    vector<string> grid1(N), grid2(N);
    for (string &str : grid1) cin >> str;
    for (string &str : grid2) cin >> str;
    
    auto rotate = [&](auto &vec) {
        for (int r0 = 0; r0 < N/2; ++r0) for (int c0 = 0; c0 < (N+1)/2; ++c0) {
            int r1 = c0,     c1 = N-1-r0;
            int r2 = N-1-r0, c2 = N-1-c0;
            int r3 = N-1-c0, c3 = r0;
            swap(vec[r0][c0], vec[r1][c1]);
            swap(vec[r0][c0], vec[r2][c2]);
            swap(vec[r0][c0], vec[r3][c3]);
        }
    };
    
    auto hamming = [&](auto &g1, auto &g2) -> int {
        int cnt = 0;
        for (int r = 0; r < N; ++r) for (int c = 0; c < N; ++c) {
            cnt += (g1[r][c] != g2[r][c]);
        }
        return cnt;
    };
    
    int ans = hamming(grid1, grid2);
    rotate(grid2), chmin(ans, hamming(grid1, grid2) + 1);
    rotate(grid2), chmin(ans, hamming(grid1, grid2) + 2);
    rotate(grid2), chmin(ans, hamming(grid1, grid2) + 1);
    cout << ans << "\n";
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
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
#define int int64
using float80 = long double;
#define double float80
using pii = pair<int, int>;
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
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

#endif
