#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int INF = LLONG_MAX >> 2;

void solve() {
    int N, _L; cin >> N >> _L;
    
    vector<int> pos(N);
    map<int, int> mp;
    for (int &x : pos) cin >> x, ++mp[x];
    sort(ALL(pos)), pos.erase(unique(ALL(pos)), end(pos));
    int n = SZ(pos);
    
    if (n >= 1000) {
        int Q; cin >> Q;
        for (int q = 1; q <= Q; ++q) {
            int S, G, T; cin >> S >> G >> T;
            cout << "No" << "\n";
        }
        return;
    }
    
    vector<int> cntL(n+1, 0), cntR(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        cntL[i] = cntL[i-1] + mp[pos[i-1]];
        cntR[i] = cntR[i-1] + mp[pos[n-i]];
    }
    
    vector dpL(n+1, vector(n+1, vector<int>(2, INF)));
    dpL[1][0][0] = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; i + j < n; ++j) {
            if (i) chmin(dpL[i+1][j][0], dpL[i][j][0] + (cntL[i] + cntR[j] + 1) * abs(pos[i]     - pos[i-1]));
            if (j) chmin(dpL[i+1][j][0], dpL[i][j][1] + (cntL[i] + cntR[j] + 1) * abs(pos[i]     - pos[n-j]));
            if (i) chmin(dpL[i][j+1][1], dpL[i][j][0] + (cntL[i] + cntR[j] + 1) * abs(pos[n-j-1] - pos[i-1]));
            if (j) chmin(dpL[i][j+1][1], dpL[i][j][1] + (cntL[i] + cntR[j] + 1) * abs(pos[n-j-1] - pos[n-j]));
        }
    }
    
    vector dpR(n+1, vector(n+1, vector<int>(2, INF)));
    dpR[0][1][1] = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 1; i + j < n; ++j) {
            if (i) chmin(dpR[i+1][j][0], dpR[i][j][0] + (cntL[i] + cntR[j] + 1) * abs(pos[i]     - pos[i-1]));
            if (j) chmin(dpR[i+1][j][0], dpR[i][j][1] + (cntL[i] + cntR[j] + 1) * abs(pos[i]     - pos[n-j]));
            if (i) chmin(dpR[i][j+1][1], dpR[i][j][0] + (cntL[i] + cntR[j] + 1) * abs(pos[n-j-1] - pos[i-1]));
            if (j) chmin(dpR[i][j+1][1], dpR[i][j][1] + (cntL[i] + cntR[j] + 1) * abs(pos[n-j-1] - pos[n-j]));
        }
    }
    
    int Q; cin >> Q;
    
    for (int q = 1; q <= Q; ++q) {
        int S, G, T; cin >> S >> G >> T;
        
        int L = lower_bound(ALL(pos), G) - begin(pos); /// # < G
        int R = n - L; /// # >= G
        
        int ans = N + min({
            (L ? abs(S - pos[1-1]) + dpL[L][R][0] + (N + 1) * abs(G - pos[L-1]) : INF),
            (L ? abs(S - pos[n-1]) + dpR[L][R][0] + (N + 1) * abs(G - pos[L-1]) : INF),
            (R ? abs(S - pos[1-1]) + dpL[L][R][1] + (N + 1) * abs(G - pos[n-R]) : INF),
            (R ? abs(S - pos[n-1]) + dpR[L][R][1] + (N + 1) * abs(G - pos[n-R]) : INF)
        });
        // cerr << ans << ": ";
        cout << (ans <= T ? "Yes" : "No") << "\n";
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

using int64 = long long;
#define int int64
using float80 = long double;
#define double float80
using pii = pair<int, int>;
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
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

#endif
