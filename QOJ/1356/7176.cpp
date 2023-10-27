#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

const vector<int> days{-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void solve() {
    int Y; cin >> Y;
    
    auto calc = [](int maxY) -> int {
        int ans = 0, d = 2; /// 1970.01.01 Thursday
        for (int y = 1970; y <= maxY; ++y) {
            // debug(y, d%7);
            for (int m = 1; m <= 12; ++m) {
                int tmp = days[m];
                if (m == 2 and y % 4 == 0) ++tmp;
                ans += (d + tmp) / 7 - (d + 1) / 7 + 1;
                d += tmp;
                // if (y == 2023) debug(y, m, d / 7 - (d - tmp + 1) / 7 + 1, d % 7);
            }
        }
        return ans;
    };
    
    cout << calc(Y) - calc(Y-1) << "\n";
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
