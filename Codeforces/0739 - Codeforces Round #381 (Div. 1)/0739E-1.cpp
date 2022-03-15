#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
using pdd = pair<double, double>;
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

#ifdef local
#define debug(...) \
    cerr << "\u001b[33m" << "LINE " << __LINE__ << ": (" << #__VA_ARGS__ << ") = ",\
    _do(__VA_ARGS__),\
    cerr << "\u001b[0m"
#define fastIO()
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", "; _do(_u...);}
#else
#define debug(...) void()
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#endif

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

const int delta = 50;

void solve() {
    int N, A, B; cin >> N >> A >> B;
    
    vector<pdd> prob(N);
    for (auto &[p, u] : prob) cin >> p;
    for (auto &[p, u] : prob) cin >> u;
    
    double max_ans = 0.0;
    for (int _ = 1; _ <= 10; ++_) {
        shuffle(ALL(prob), rng);
        vector<vector<double>> dp(A+1, vector<double>(B+1, 0.000));
        for (int id = 0; id < N; ++id) {
            auto [p, u] = prob[id];
            for (int i = min(A*id/N+delta, A); i >= max(A*id/N-delta, 0); --i) {
                for (int j = min(B*id/N+delta, B); j >= max(B*id/N-delta, 0); --j) {
                    if (i) chmax(dp[i][j], dp[i-1][j] + p);
                    if (j) chmax(dp[i][j], dp[i][j-1] + u);
                    if (i and j) chmax(dp[i][j], dp[i-1][j-1] + 1.0 - (1.0 - p) * (1.0 - u));
                }
            }
        }
        chmax(max_ans, dp[A][B]);
    }
    cout << fixed << setprecision(10) << max_ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}
