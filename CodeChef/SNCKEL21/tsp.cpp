#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ef push_front
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int INF = INT_MAX >> 1;

vector<vector<int>> c, dp;

void solve() {
    int N, D; cin >> N >> D;
    
    c.assign(N, vector<int>(N, INF));
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) cin >> c[i][j], c[j][i] = c[i][j];
    }
    
    dp.assign(N, vector<int>(N, INF));
    dp[0][0] = 0;
    for (int i = 0; i < N-1; ++i) {
        for (int j = 0; j < N-1; ++j) {
            int k = max(i, j);
            chmin(dp[i][k+1], dp[i][j] + c[j][k+1]);
            chmin(dp[k+1][j], dp[i][j] + c[i][k+1]);
        }
    }
    
    int min_ans = INF;
    for (int i = 0; i < N-1; ++i) chmin(min_ans, dp[i][N-1] + c[i][N-1]);
    for (int j = 0; j < N-1; ++j) chmin(min_ans, dp[N-1][j] + c[j][N-1]);
    cout << D * (2*N-2) + min_ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}
