#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

void solve() {
    int N, M; cin >> N >> M;
    
    if (N == 1 and M == 1) {
        cout << 1 << "\n";
        cout << 1 << " " << 1 << "\n";
        return;
    }
    
    bool flag_swap = false;
    if (N == M) --N;
    if (N > M) swap(N, M), flag_swap = true;
    
    vector<pii> bishops;
    for (int c1 = 1, c2 = M; c1 + N <= c2; c1 += N, c2 -= N) {
        for (int r = 1; r <= N; ++r) bishops.eb(r, c1), bishops.eb(r, c2);
        if (c1 + 3*N > c2) {
            if (c1 + 2*N <= c2) {
                c1 += N;
                for (int r = 1; r <= N; ++r) bishops.eb(r, c1);
            }
            if (N % 2 == 1) {
                for (int r = (N+1)/2, c = c1+N/2+1; c <= c2-N/2-1; ++c) bishops.eb(r, c);
            }
            else {
                int c = (c1 + c2) / 2, k = N - (c - c1);
                for (int r = k+1; r <= N-k; ++r) bishops.eb(r, c);
                if (N - 2*k == 1 and c - c1 != c2 - c) bishops.eb(k+1, c+1);
            }
        }
    }
    
    cout << SZ(bishops) << "\n";
    for (auto [r, c] : bishops) {
        if (flag_swap) cout << c << " " << r << "\n";
        else           cout << r << " " << c << "\n";
    }
    
    // vector<string> board(N, string(M, '.'));
    // for (auto [r, c] : bishops) board[r-1][c-1] = 'x';
    // for (string &str : board) debug(str);
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

#define X first
#define Y second
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
