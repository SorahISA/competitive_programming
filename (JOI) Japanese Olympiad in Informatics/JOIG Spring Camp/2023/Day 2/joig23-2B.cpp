#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

struct SegTree {
    
    int maxn, INF;
    vector<int> seg;
    
    void init(int N, int inf) {
        maxn = 1 << (__lg(N) + 1);
        INF = inf;
        seg.assign(2*maxn, INF);
    }
    
    void modify_point_add(int qX, int val) {
        seg[qX += maxn] += val;
        while ((qX >>= 1) >= 1) seg[qX] = min(seg[qX<<1], seg[qX<<1|1]);
    }
    
    void modify_point_chmin(int qX, int val) {
        chmin(seg[qX += maxn], val);
        while ((qX >>= 1) >= 1) seg[qX] = min(seg[qX<<1], seg[qX<<1|1]);
    }
    
    int query_range_min(int qL, int qR) {return query_range_min(qL, qR, 1, 0, maxn-1);}
    int query_range_min(int qL, int qR, int now, int nL, int nR) {
        if (qL <= nL and nR <= qR) return seg[now];
        
        int nM = (nL + nR) >> 1, ans = INF;
        if (qL <= nM) chmin(ans, query_range_min(qL, qR, now<<1,   nL,   nM));
        if (nM <  qR) chmin(ans, query_range_min(qL, qR, now<<1|1, nM+1, nR));
        
        return ans;
    }
};

void solve() {
    int N, K; cin >> N >> K;
    string S; cin >> S, S += "R";
    
    if (K == 1) {
        string res = "B";
        for (int i = 0; i < SZ(S); ++i) {
            if (S[i] == 'R' and res.back() == 'B') res += "R";
            if (S[i] == 'G' and res.back() == 'R') res += "G";
            if (S[i] == 'B' and res.back() == 'G') res += "B";
        }
        cout << N - (SZ(res) - 1) / 3 * 3 << "\n";
        return;
    }
    
    SegTree stR, stG, stB;
    stR.init(K, N+1), stG.init(K, N+1), stB.init(K, N+1);
    
    for (int i = 0; i <= N; ++i) {
             if (S[i] == 'R') stR.modify_point_chmin(i%K, min(stB.query_range_min(0, K-1), (i+K-1)/K));
        else if (S[i] == 'G') stG.modify_point_chmin(i%K, stR.query_range_min(0, K-1));
        else if (S[i] == 'B') stB.modify_point_chmin(i%K, stG.query_range_min(0, K-1));
        stR.modify_point_add((i-1+K)%K, 1);
        stG.modify_point_add((i-1+K)%K, 1);
        stB.modify_point_add((i-1+K)%K, 1);
        // debug(i);
        // for (int j = 0; j < K; ++j) debug("R", stR.query_range_min(j, j));
    }
    cout << stR.query_range_min(N%K, N%K) << "\n";
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
