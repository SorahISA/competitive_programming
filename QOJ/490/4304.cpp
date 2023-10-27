#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

void solve() {
    int N, W; cin >> N >> W;
    int half = W / 2;
    
    vector<tuple<int, int, int>> small, large;
    for(int i = 1; i <= N; ++i) {
        int w, c; cin >> w >> c;
        if (w > W) continue;
        if (w > half) large.eb(w, c, i);
        else          small.eb(w, c, i);
    }
    large.eb(0, 0, 0);
    
    sort(ALL(small), [&](const auto &a, const auto &b) {
        const auto &[wa, ca, ia] = a;
        const auto &[wb, cb, ib] = b;
        return ca * wb > wa * cb;
    });
    sort(ALL(large), [&](const auto &a, const auto &b) {
        const auto &[wa, ca, ia] = a;
        const auto &[wb, cb, ib] = b;
        return wa > wb;
    });
    
    int max_val = 0, max_val_large_id = -1;
    for(int tok_small = 0, cap = W + half, val = 0; auto [wl, cl, il] : large) {
        cap -= wl, val += cl;
        for (; tok_small < SZ(small); ++tok_small) {
            auto [ws, cs, is] = small[tok_small];
            if (cap < ws) break;
            cap -= ws, val += cs;
        }
        if (chmax(max_val, val)) max_val_large_id = il;
        cap += wl, val -= cl;
    }
    // debug(max_val_large_id, max_val);
    
    vector<int> pick;
    for (auto [wl, cl, il] : large) {
        if (il != max_val_large_id) continue;
        if (il) pick.eb(il);
        int cap = W + half - wl;
        for (int i = 0; i < SZ(small); ++i) {
            auto [ws, cs, is] = small[i];
            if (cap < ws) break;
            cap -= ws, pick.eb(is);
        }
        break;
    }
    sort(ALL(pick));
    
    cout << SZ(pick) << "\n";
    for (int i = 0, sz = SZ(pick); i < sz; ++i) cout << pick[i] << " \n"[i == sz-1];
}

signed main() {
    IOS();
    int t = 1; cin >> t;
    for (int i = 1; i <= t; ++i) solve();
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
template <typename T> using MaxHeap = std::priority_queue<T>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)

#ifdef local
#define IOS() void()
#define debug(...) \
    fprintf(stderr, "%sAt [%s], line %d: (%s) = ", "\u001b[33m", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), fprintf(stderr, "%s", "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#define debug(...) void()
#define endl '\n'
#endif

// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

#endif
