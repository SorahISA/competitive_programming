#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int INF = 2'100'000'000;
const int lgC = 32;

void solve() {
    int N; cin >> N;
    
    vector<int> X(N+2);
    for (int i = 1; i <= N; ++i) cin >> X[i];
    X[0] = X[1] - INF, X[N+1] = X[N] + INF; /// add two dummy nodes which will only be visited last
    
    vector<vector<int>> dist(lgC);
    for (int i = 1; i < N+2; ++i) {
        for (int j = 0; j < lgC; ++j) {
            if ((X[i] - X[i-1]) >> j) dist[j].eb(i);
        }
    }
    
    int Q; cin >> Q;
    
    for (int q = 1; q <= Q; ++q) {
        int S; cin >> S;
        
        if (N == 1) {cout << abs(S - X[1]) << "\n"; continue;}
        
        int ans = 0, pos = -1;
        if (S <= X[1]) pos = 1;
        else if (S >= X[N]) pos = N;
        else {
            pos = lower_bound(ALL(X), S) - begin(X);
            if (S - X[pos-1] <= X[pos] - S) --pos;
        }
        ans += abs(S - X[pos]);
        
        int dir = -1, posL = pos, posR = pos;
        if (X[pos] - X[pos-1] <= X[pos+1] - X[pos]) dir = 0, --posL;
        else                                        dir = 1, ++posR;
        
        for (int L = 0; L < lgC; ++L) {
            // debug(L, posL, posR);
            if (dir == 0) {
                int p = *prev(upper_bound(ALL(dist[L]), posL)); /// find <= posL
                if (X[posR+1] - X[p] <  X[p] - X[p-1]) posL = p, ans += X[posR] - X[posL], dir = 1, ++posR;
                else                                   posL = p-1;
            }
            else if (dir == 1) {
                int p = *upper_bound(ALL(dist[L]), posR) - 1; /// find > posR and sub 1
                if (X[p] - X[posL-1] <= X[p+1] - X[p]) posR = p, ans += X[posR] - X[posL], dir = 0, --posL;
                else                                   posR = p+1;
            }
            if (posL == 0 or posR == N+1) {ans += X[posR] - X[posL] - INF; break;}
        }
        
        cout << ans << "\n";
    }
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
#define double __float80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
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
    fprintf(stderr, "\u001b[33mAt [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

#endif
