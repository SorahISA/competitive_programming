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
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int maxn = 1 << 19;

namespace BIT {

bitset<maxn> BIT;

void add(int idx) {
    while (idx < maxn) BIT[idx] = 1, idx += idx & -idx;
}

bool ask(int idx, bool ans = false) {
    while (idx) ans |= BIT[idx], idx -= idx & -idx;
    return ans;
}

}

void solve() {
    int N; cin >> N;
    
    vector<pii> pts(N);
    vector<int> all_y;
    for (auto &[x, e] : pts) cin >> x >> e, tie(x, e) = pair(x-e, -(x+e)), all_y.eb(e);
    sort(ALL(pts));
    sort(ALL(all_y)), all_y.erase(unique(ALL(all_y)), end(all_y));
    
    int ans = 0;
    for (auto &[x, y] : pts) {
        // debug(x, y);
        y = lower_bound(ALL(all_y), y) - begin(all_y) + 1;
        ans += !BIT::ask(y), BIT::add(y);
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
