#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int INF = INT_MAX;

void solve() {
    int N; cin >> N;
    
    vector<vector<int>> cards(N);
    for (int i = 0; i < N; ++i) {
        int a, c; cin >> a >> c, --c;
        cards[c].eb(a);
    }
    for (int c = 0; c < N; ++c) {
        if (SZ(cards[c])) nth_element(rbegin(cards[c]), rend(cards[c]) - 1, rend(cards[c]));
    }
    
    vector<int> pmax(N, -INF), smax(N, -INF);
    for (int c = 0; c < N; ++c) { if (SZ(cards[c])) pmax[c] = smax[c] = cards[c][0]; }
    for (int c = 1; c < N; ++c) chmax(pmax[c], pmax[c-1]), chmax(smax[N-c-1], smax[N-c]);
    
    int ans = 0;
    for (int c = 0; c < N; ++c) {
        int mx = max(
            (c > 0   ? pmax[c-1] : -INF),
            (c < N-1 ? smax[c+1] : -INF)
        );
        for (int i = 1; i < SZ(cards[c]); ++i) ans += max(mx + cards[c][i], int(0));
    }
    for (int c = 0; c < N; ++c) {
        if (SZ(cards[c])) ans += max(smax[0] + cards[c][0], int(0));
    }
    ans -= max(smax[0] + smax[0], int(0));
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
