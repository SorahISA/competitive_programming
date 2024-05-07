#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int INF = LLONG_MAX >> 2;

void solve() {
    int N; cin >> N;
    
    vector<int> A(N);
    for (int &x : A) cin >> x;
    sort(ALL(A));
    
    vector<int> dp(N);
    dp[0] = INF, dp[1] = A[1] - A[0];
    if (N >= 3) dp[2] = A[2] - A[0];
    for (int i = 3; i < N; ++i) {
        dp[i] = min(dp[i-2] + A[i] - A[i-1], dp[i-3] + A[i] - A[i-2]);
    }
    cout << dp[N-1] << "\n";
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
