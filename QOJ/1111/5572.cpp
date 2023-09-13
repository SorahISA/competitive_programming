#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize ("unroll-loops", "Ofast")
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define double __float80
using pii = pair<int,int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
// #define X first
// #define Y second

template <size_t D, typename T> struct Vec : vector<Vec<D-1, T>> {
    template <typename ... U> Vec(int n = 0, U ... _u) : vector<Vec<D-1, T>>(n, Vec<D-1, T>(_u...)) {}
};
template <typename T> struct Vec<1, T> : vector<T> {
    Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
};

#ifdef local
#define debug(...) \
    fprintf(stderr, "\e[1;93mAt [%s], Line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\e[0m")
template <typename T> void _do(T &&_x) {cerr << _x << endl;}
template <typename T, typename ...S> void _do(T &&_x, S &&..._t) {cerr << _x << ", "; _do(_t...);}
#define IOS() void()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#define endl "\n"
#define debug(...) void()
#endif

template <typename U, typename V> bool chmin(U &lhs, V rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename U, typename V> bool chmax(U &lhs, V rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    Vec<2, char> board(N, N, '.');
    
    if (N == 1) {
        board[0][0] = 'L';
    }
    
    else if (N & 1) {
        for (int r = 0, lo = 0, hi = N-1; r < N; ++r) {
            for (int c = lo; c <= hi; c += 2) board[r][c] = 'U', board[N-r-1][N-c-1] = 'D';
            lo += 1, hi -= 1;
        }
        for (int c = 0, lo = 1, hi = N-2; c < N; ++c) {
            for (int r = lo; r <= hi; r += 2) board[r][c] = 'L', board[N-r-1][N-c-1] = 'R';
            lo += 1, hi -= 1;
        }
        board[N/2][N/2] = '.', board[N/2-1][N/2] = 'D', board[N/2+1][N/2] = 'U';
    }
    
    else {
        for (int c = 0, lo = 0, hi = N-2; c < N; ++c) {
            for (int r = lo; r <= hi; r += 2) board[r][c] = 'L', board[N-r-1][N-c-1] = 'R';
            (c & 1 ? hi -= 2 : lo += 2);
        }
        for (int r = 0, lo = 1, hi = N-1; r < N; ++r) {
            for (int c = lo; c <= hi; c += 2) board[r][c] = 'U', board[N-r-1][N-c-1] = 'D';
            (r & 1 ? lo += 2 : hi -= 2);
        }
    }
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) cout << board[i][j];
        cout << "\n";
    }
}

signed main(){
    IOS();
    int t = 1; // cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}
