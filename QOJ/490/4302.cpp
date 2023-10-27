#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

void solve() {
    int n,m,k,s;
    cin >> n >> m >> s;
    vector<int> cards(m);
    for (int i = 0; i < m; ++i) {
        cin >> cards[i];
    }
    sort(ALL(cards));
    cards.erase(unique(ALL(cards)), end(cards));
    // debug(SZ(cards));
    k = SZ(cards);
    
    vector<pii> rng;
    for (int l = k-1, r = k-1; l >= 0; --l) {
        while (cards[r] - cards[l] >= m or cards[r] - cards[l] - r + l > s) --r;
        int L = min(max(cards[l] - (cards[r] - cards[l] - r + l), cards[r] - m + 1), (l+m-s-1 <= r ? cards[l+m-s-1] - m + 1 : n+1));
        int R = cards[l];
        debug(l, r, L, R, cards[r] - cards[l] - r + l);
        if (r-l+1+s >= m and L <= R) rng.eb(L, R);
    }
    sort(ALL(rng));
    
    int ans = 0;
    for (int lst = 0; auto [l, r] : rng) {
        debug(l, r);
        chmin(r, n-m+1), chmax(l, lst+1);
        ans += max(r, lst) - l + 1;
        chmax(lst, r);
    }
    cout << ans << "\n";
    
    
    // vector<pii> inv;
    // int lst = 0;
    // int r = 1;
    // int cnt = 0;
    // for (int i = 0; i < SZ(cards); ++i) {
    //     while (r < SZ(cards) && cards[r] - cards[i] - (r - i) <= s) {
    //         r++;
    //     }
    //     int len = cards[r-1] - cards[i] + 1;
    //     int budget = s - cnt;
        
    //     int R = min(n, cards[r-1] + budget);
        
    //     int L = max(int(1), cards[i] - budget);
    //     int R = cards[i];
        
    //     if (cards[r-1] - L + 1 < m) {
            
    //     }
    //     else {
    //         inv.eb(L, R); // [L, R]
    //     }
    // }
    // int lst = 0;
    // int ans = 0;
    // cout << ans << '\n';
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
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
