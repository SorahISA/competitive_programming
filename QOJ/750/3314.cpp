#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

const int INF = INT_MAX >> 1;

void solve() {
    string S, T; cin >> S >> T;
    int N = SZ(S), M = SZ(T);
    S = '.' + S, T = '.' + T; /// 0-based to 1-based
    
    Vec<2, int> s_nxt(N+2, 2, N+1), t_nxt(M+2, 2, M+1);
    for (int i = N, nxt_0 = N+1, nxt_1 = N+1; i >= 0; --i) {
        s_nxt[i][0] = nxt_0, s_nxt[i][1] = nxt_1;
        if (i) (S[i] == '0' ? nxt_0 : nxt_1) = i;
    }
    for (int i = M, nxt_0 = M+1, nxt_1 = M+1; i >= 0; --i) {
        t_nxt[i][0] = nxt_0, t_nxt[i][1] = nxt_1;
        if (i) (T[i] == '0' ? nxt_0 : nxt_1) = i;
    }
    
    Vec<2, int> dp(N+2, M+2, INF);
    dp[0][0] = 0;
    for (int i = 0; i <= N+1; ++i) {
        for (int j = 0; j <= M+1; ++j) {
            chmin(dp[s_nxt[i][0]][t_nxt[j][0]], dp[i][j] + 1);
            chmin(dp[s_nxt[i][1]][t_nxt[j][1]], dp[i][j] + 1);
        }
    }
    
    // cerr << "\u001b[34m";
    // for (int i = 0; i <= N+1; ++i) {
    //     for (int j = 0; j <= M+1; ++j) {
    //         cerr << setw(2) << dp[i][j] << " \n"[j == M+1];
    //     }
    // }
    // cerr << "\u001b[0m";
    
    Vec<2, int> valid(N+2, M+2, 0);
    valid[N+1][M+1] = 1;
    for (int i = N+1; i >= 0; --i) {
        for (int j = M+1; j >= 0; --j) {
            if (dp[s_nxt[i][0]][t_nxt[j][0]] == dp[i][j] + 1) valid[i][j] |= valid[s_nxt[i][0]][t_nxt[j][0]];
            if (dp[s_nxt[i][1]][t_nxt[j][1]] == dp[i][j] + 1) valid[i][j] |= valid[s_nxt[i][1]][t_nxt[j][1]];
        }
    }
    
    // cerr << "\u001b[35m";
    // for (int i = 0; i <= N+1; ++i) {
    //     for (int j = 0; j <= M+1; ++j) {
    //         cerr << setw(2) << valid[i][j] << " \n"[j == M+1];
    //     }
    // }
    // cerr << "\u001b[0m";
    
    string ans = "";
    int now_i = 0, now_j = 0;
    while (now_i != N+1 or now_j != M+1) {
        if (
            valid[s_nxt[now_i][0]][t_nxt[now_j][0]] and
            dp[s_nxt[now_i][0]][t_nxt[now_j][0]] == dp[now_i][now_j] + 1
        ) {
            ans += "0", now_i = s_nxt[now_i][0], now_j = t_nxt[now_j][0];
        }
        else if (
            valid[s_nxt[now_i][1]][t_nxt[now_j][1]] and
            dp[s_nxt[now_i][1]][t_nxt[now_j][1]] == dp[now_i][now_j] + 1
        ) {
            ans += "1", now_i = s_nxt[now_i][1], now_j = t_nxt[now_j][1];
        }
        else exit(-1);
    }
    cout << ans << "\n";
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize ("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
// #define double __float80
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) ((int)(a).size())
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
    template <typename... U> Vec(int n = 0, U ... _u) : vector<Vec<D-1, T>>(n, Vec<D-1, T>(_u...)) {}
};
template <typename T> struct Vec<1, T> : vector<T> {
    Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
};

#ifdef local
#define IOS() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << endl;}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#define debug(...) void()
#define endl '\n'
#endif

template <typename U, typename V> bool chmin(U &u, V v) {return u > v ? u = v, 1 : 0;}
template <typename U, typename V> bool chmax(U &u, V v) {return u < v ? u = v, 1 : 0;}

#endif
