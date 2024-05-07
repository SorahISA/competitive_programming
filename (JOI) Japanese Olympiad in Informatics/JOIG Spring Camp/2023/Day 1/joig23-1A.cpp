#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int INF = INT_MAX >> 1;

void solve() {
    int N, Q; cin >> N >> Q;
    
    vector<pii> buildings(N);
    for (auto &[x, h] : buildings) cin >> x >> h;
    buildings.eb(0, 0);
    buildings.eb(INF, INF);
    sort(ALL(buildings), [](pii b1, pii b2) {
        if (b1.first == b2.first) return b1.second > b2.second;
        return b1.first < b2.first;
    });
    
    vector<pii> _buildings;
    for (int maxh = -1; auto [x, h] : buildings) {
        if (chmax(maxh, h)) _buildings.eb(x, h); //, debug(x, h);
    }
    buildings.swap(_buildings);
    
    for (int q = 1; q <= Q; ++q) {
        int T; cin >> T;
        
        int lo = 0, hi = SZ(buildings), mi;
        while (lo < hi) {
            mi = (lo + hi + 1) >> 1;
            auto [x, h] = buildings[mi];
            if (T >= x + h) lo = mi;
            else            hi = mi - 1;
        }
        // debug(lo);
        
        cout << max(
            min(T - buildings[lo  ].first, buildings[lo  ].second),
            min(T - buildings[lo+1].first, buildings[lo+1].second)
        ) << "\n";
    }
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

// #define int int64_t
#define double __float80
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
    fprintf(stderr, "\u001b[33mAt [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

#endif
