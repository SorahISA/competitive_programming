#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

void solve() {
    int N, K; cin >> N >> K;
    
    vector<tuple<int, int, int>> phones(N);
    for (auto &[B, A, C] : phones) cin >> A >> B >> C;
    sort(ALL(phones));
    
    int ans = 0;
    set<pii> rng{{1, K}};
    for (auto &[B, A, C] : phones) {
        // debug(A, B, C);
        // for (auto [l, r] : rng) debug(l, r);
        
        auto it = rng.lower_bound({A, K+1});
        if (it != begin(rng) and prev(it)->second >= A) it = prev(it);
        if (it == end(rng)) continue;
        
        auto [L, R] = *it;
        if (L < A) rng.erase(it), rng.ee(L, A-1), rng.ee(A, R);
        // debug(L, R);
        
        it = rng.lower_bound({A, 0});
        while (C > 0 and it != end(rng)) {
            tie(L, R) = *it, it = rng.erase(it);
            // debug(L, R);
                 if (R <= B and L+C > R)                 ans += R-L+1, C -= R-L+1;
            else if (R >  B and L+C > B) rng.ee(B+1, R), ans += B-L+1, C = 0;
            else                         rng.ee(L+C, R), ans += C,     C = 0;
        }
        // debug(ans);
        
        if (!SZ(rng)) break;
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
