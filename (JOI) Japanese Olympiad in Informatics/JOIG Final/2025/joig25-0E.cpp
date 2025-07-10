#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

struct SegTree {
    
    vector<int> seg;
    int maxn;
    
    void init(int N) {
        maxn = 2 << __lg(N+1);
        seg.assign(2*maxn, 0);
    }
    
    void modify_point_val(int qX, int val) {
        seg[qX += maxn] = val;
        while ((qX >>= 1)) chmax(seg[qX], max(seg[qX<<1], seg[qX<<1|1]));
    }
    
    int query_range_max(int qL, int qR) {
        int ans = max(seg[qL += maxn], seg[qR += maxn]);
        while (qL + 1 < qR) {
            if (~qL & 1) chmax(ans, seg[qL ^ 1]);
            if ( qR & 1) chmax(ans, seg[qR ^ 1]);
            qL >>= 1, qR >>= 1;
        }
        return ans;
    }
    
};

void solve() {
    int N; cin >> N;
    
    vector<int> A(2*N), V(N);
    for (int &x : A) cin >> x, --x;
    for (int &x : V) cin >> x;
    
    vector<array<int, 3>> itvs(N, {-1, -1, -1});
    for (int i = 0; i < N; ++i) itvs[i][2] = V[i];
    for (int i = 0; i < 2*N; ++i) {
        if (itvs[A[i]][0] == -1) itvs[A[i]][0] = i;
        else                     itvs[A[i]][1] = i;
    }
    sort(ALL(itvs), [&](auto &a1, auto &a2) { return a1[1] < a2[1]; });
    
    // for (auto [l, r, v] : itvs) debug(l, r, v);
    
    int ans = *max_element(ALL(V));
    vector<array<int, 2>> dp(N, {0, 0});
    SegTree dp0, dp1; dp0.init(2*N), dp1.init(2*N);
    for (int i = 0; i < N; ++i) {
        // dp[i][0] = dp[i][1] = itvs[i][2];
        // for (int j = i-1; j >= 0; --j) {
        //     if (itvs[j][1] < itvs[i][0]) chmax(dp[i][0], dp[j][1] + itvs[i][2]);
        //     if (itvs[j][0] < itvs[i][0]) chmax(dp[i][1], dp[j][0] + itvs[i][2]);
        // }
        dp[i][0] = dp1.query_range_max(0, itvs[i][0]) + itvs[i][2];
        dp[i][1] = dp0.query_range_max(0, itvs[i][0]) + itvs[i][2];
        chmax(dp[i][1], dp[i][0]);
        dp0.modify_point_val(itvs[i][0], dp[i][0]);
        dp1.modify_point_val(itvs[i][1], dp[i][1]);
        chmax(ans, dp[i][1]);
    }
    cout << ans << "\n";
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
