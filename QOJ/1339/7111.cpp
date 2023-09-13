#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

const int INF = INT_MAX;

void solve() {
    int A, B, C, D; cin >> A >> B >> C >> D;
    int V, T; cin >> V >> T;
    
    int lcm = A * C / gcd(A, C), tA = C / gcd(A, C), tC = A / gcd(A, C);
    
    vector<pii> press{{0, 0}};
    for (int i = 1; i < tA; ++i) press.eb(A*i, B);
    for (int i = 1; i < tC; ++i) press.eb(C*i, D);
    press.eb(lcm, B+D);
    sort(ALL(press));
    
    vector<int> state(SZ(press));
    for (int i = 0, lst = 0; i < SZ(press); ++i) {
        auto [now, cnt] = press[i];
        state[i] = cnt - (now - lst > V);
        lst = now;
    }
    partial_sum(ALL(state), begin(state));
    
    int counter = (B+D-1) + end(state)[-1] * (T / lcm);
    counter += state[upper_bound(ALL(press), pii{T % lcm, INF}) - begin(press) - 1];
    
    cout << counter << "\n";
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

#endif
