#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

void solve() {
    int N; cin >> N;
    string S; cin >> S;
    
    vector<int> lst(N, -1), nxt(N, N);
    for (int i = 0, s = -1, p = -1; i < N; ++i) {
        if (S[i] == 's') s = i;
        if (S[i] == 'p') p = i, lst[i] = s;
        if (S[i] == 'b') lst[i] = p;
    }
    for (int i = N-1, u = N, s = N; i >= 0; --i) {
        if (S[i] == 'u') u = i;
        if (S[i] == 's') s = i, nxt[i] = u;
        if (S[i] == 'b') nxt[i] = s;
    }
    
    int ans = N * N;
    for (int i = 0; i < N; ++i) {
        if (S[i] == 'b' and lst[i] != -1 and lst[lst[i]] != -1 and nxt[i] != N and nxt[nxt[i]] != N) {
            // debug(lst[lst[i]], lst[i], i, nxt[i], nxt[nxt[i]]);
            chmin(ans, (i - lst[lst[i]] - 2) + (i - lst[i] - 1) + (nxt[i] - i - 1) + (nxt[nxt[i]] - i - 2));
        }
    }
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

#endif
