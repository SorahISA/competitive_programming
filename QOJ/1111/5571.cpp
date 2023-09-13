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
    string S; cin >> S;
    int N, mod; cin >> mod, N = SZ(S);
    
    Vec<2, int> pcntL(128, 128, 0), pcntR(128, 128, 0);
    vector<int> cntL(128, 0), cntR(128, 0);
    
    for (int i = N-1; i >= 0; --i) {
        for (int j = 33; j <= 126; ++j) pcntR[S[i]][j] += cntR[j];
        ++cntR[S[i]];
    }
    
    int ans = 0, lastans = 0;
    for (int i = 0; i < N; ++i) {
        --cntR[S[i]];
        for (int j = 33; j <= 126; ++j) pcntR[S[i]][j] -= cntR[j], lastans -= pcntL[j][S[i]] * cntR[j];
        ans = (ans + (lastans %= mod) + mod) % mod;
        // debug(i, lastans);
        for (int j = 33; j <= 126; ++j) pcntL[j][S[i]] += cntL[j], lastans += pcntR[S[i]][j] * cntL[j];
        ++cntL[S[i]];
    }
    cout << ans << "\n";
}

signed main(){
    IOS();
    int t = 1; // cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}
