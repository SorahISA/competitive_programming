#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

void solve() {
    int N, M; cin >> N >> M;
    
    vector<pii> exc(N);
    for (auto &[t, c] : exc) cin >> t >> c;
    
    vector<int> ans(M+1, 0), dp(M+1, 0);
    for (int i = 1, ticket = 1; i <= M; ++ticket) {
        dp[ticket] = dp[ticket - 1];
        for (auto [t, c] : exc) {
            if (ticket >= t) chmax(dp[ticket], dp[ticket - t + c] + c);
        }
        while (i <= min(ticket + dp[ticket], M)) ans[i++] = ticket;
        // debug(ticket, dp[ticket]);
    }
    
    for (int i = 1; i <= M; ++i) cout << ans[i] << "\n";
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

using i64 = long long;
#define int i64
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define ee emplace
#define eb emplace_back
#define pb pop_back
#define ef emplace_front
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
