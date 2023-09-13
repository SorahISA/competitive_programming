#define _GLIBCXX_DEBUG 1
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define int long long
using pii = pair<int,int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define ee emplace
#define eb emplace_back
#define ef emplace_front
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
#define IOS()
#define debug(...) \
    fprintf(stderr, "\e[1;93mAt [%s], Line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\e[0m")
template <typename T> void _do(T &&_x) {cerr << _x << endl;}
template <typename T, typename ...S> void _do(T &&_x, S && ..._t) {cerr << _x << ", "; _do(_t...);}
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#define endl '\n'
#define debug(...)
#endif

template <typename U, typename V> bool chmin(U &u, V v) {return u > v ? u = v, 1 : 0;}
template <typename U, typename V> bool chmax(U &u, V v) {return u < v ? u = v, 1 : 0;}

const int INF = INT_MAX;

void solve() {
    int N; cin >> N;
    
    // Vec<2, int> _dis(N, N, INF);
    // for (int i = 0; i < N; ++i) {
        // if (i) {
            // int par = rand() % i;
            // _dis[i][par] = _dis[par][i] = 1;
        // }
        // for (int j = i; j < N; ++j) {
            // if (i == j) _dis[i][j] = 0;
            // else if (rand() % 5 == 0) _dis[i][j] = _dis[j][i] = 1;
        // }
    // }
    
    // for (int i = 0; i < N; ++i) {
        // for (int j = i+1; j < N; ++j) {
            // if (_dis[i][j] == 1) debug(i, j);
        // }
    // }
    
    // for (int k = 0; k < N; ++k) {
        // for (int i = 0; i < N; ++i) {
            // for (int j = 0; j < N; ++j) {
                // chmin(_dis[i][j], _dis[i][k] + _dis[k][j]);
            // }
        // }
    // }
    
    vector<string> board(N);
    for (string &str : board) cin >> str;
    // for (int i = 0; i < N; ++i) {
        // board[i].resize(N);
        // for (int j = 0; j < N; ++j) board[i][j] = char('0' + (_dis[i][j] & 1));
    // }
    
    // for (string str : board) debug(str);
    
    vector<pii> edges;
    Vec<2, int> dis(N, N, INF);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j) dis[i][j] = 0;
            else if (board[i][j] == '1') {
                dis[i][j] = 1;
                if (i < j) edges.eb(i, j);
            }
        }
    }
    
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                chmin(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            if (dis[i][j] != 1 and dis[i][j] % 2 != 0) return cout << "NO" << "\n", void();
        }
    }
    
    cout << "YES" << "\n";
    cout << SZ(edges) << "\n";
    for (auto [u, v] : edges) cout << u+1 << " " << v+1 << "\n";
}

signed main() {
    // srand(time(0));
    IOS();
    int t = 1; cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}
