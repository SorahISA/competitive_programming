#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

const int maxn = 30;

vector cnm(maxn, vector<int>(maxn));

void recur(int &ans, const int &K, int sum, int lst, int way) {
    if (lst >= 3) {
        for (int i = 2; i < lst; ++i) {
            for (int j = 1; j <= sum/i; ++j) {
                recur(ans, K, sum - i*j, i, way * cnm[j+K-1][j]);
            }
        }
    }
    ans += way * cnm[sum+K-1][sum];
}

void solve() {
    int N, K; cin >> N >> K;
    
    int ans = 0;
    recur(ans, K, N, N+1, 1);
    cout << ans << "\n";
}

void init() {
    for (int i = 0; i < maxn; ++i) cnm[i][0] = cnm[i][i] = 1;
    for (int i = 2; i < maxn; ++i) {
        for (int j = 1; j < i; ++j) cnm[i][j] = cnm[i-1][j-1] + cnm[i-1][j];
    }
}

signed main() {
    IOS();
    init();
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
