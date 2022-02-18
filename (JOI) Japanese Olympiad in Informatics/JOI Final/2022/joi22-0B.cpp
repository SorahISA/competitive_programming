#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define ee emplace
#define eb emplace_back
#define ef push_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    cerr << "\u001b[33m" << "At func " << __FUNCTION__ << ", line " << __LINE__ << ": ",\
    cerr << "(" << #__VA_ARGS__ << ") = ",\
    _do(__VA_ARGS__),\
    cerr << "\u001b[0m"
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int INF = LLONG_MAX >> 2;

inline int divceil(int x, int y) {
    if (y < 0) x *= -1, y *= -1;
    if (x <= 0) return x / y;
    return (x - 1) / y + 1;
}

void solve() {
    int N, M; cin >> N >> M;
    
    vector<int> A(N), B(N);
    for (int &x : A) cin >> x;
    for (int &x : B) cin >> x;
    for (int i = 0; i < N; ++i) chmax(A[i], B[i]);
    
    auto calc = [&](int val) -> bool {
        __int128 give = 0, need = 0;
        for (int i = 0; i < N; ++i) {
            // debug(val, A[i], B[i], M - divceil(val, A[i]), divceil(val - A[i] * M, B[i]));
            give += max(M - divceil(val, A[i]), (int)0);
            need += max(divceil(val - A[i] * M, B[i]), (int)0);
        }
        return give >= need;
    };
    
    int lo = 0, hi = INF, mi;
    while (lo < hi) {
        mi = (lo + hi + 1) >> 1;
        if (calc(mi)) lo = mi;
        else          hi = mi - 1;
    }
    cout << lo << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
