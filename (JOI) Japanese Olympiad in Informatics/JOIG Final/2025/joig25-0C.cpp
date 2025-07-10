#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

void solve() {
    int N, Q; cin >> N >> Q;
    string S; cin >> S;
    
    vector<string> votes{S};
    for (int i = 0; i < N; ++i) {
        votes.eb("");
        for (int j = 0; j < SZ(votes[i]); j += 3) {
            if (votes[i][j] == votes[i][j+1]) votes.back() += votes[i][j];
            else                              votes.back() += votes[i][j+2];
        }
    }
    
    for (int q = 1; q <= Q; ++q) {
        int p; cin >> p, --p, votes[0][p] = (votes[0][p] == 'A' ? 'B' : 'A');
        for (int i = 0; i < N; ++i, p /= 3) {
            if (votes[i][p/3*3] == votes[i][p/3*3+1]) votes[i+1][p/3] = votes[i][p/3*3];
            else                                      votes[i+1][p/3] = votes[i][p/3*3+2];
        }
        cout << votes[N][0] << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using i64 = long long;
#define int i64
using f64 = double;
using f80 = long double;
#define double f80
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

template <typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) { cerr << _t << "\n"; }
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) { cerr << _t << ", ", _do(_u...); }
#else
#define fastIO() cin.tie(0)->sync_with_stdio(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

#endif
