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
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At func [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int maxn = 1 << 18;

struct FenwickTree {
    vector<int> BIT;
    FenwickTree(int sz) : BIT(sz, 0) {}
    inline void add(int idx, int val) {while (idx < maxn) BIT[idx] += val, idx += idx & -idx;}
    inline void modify_point_add(int qX, int val) {add(qX+1, val);}
    inline int ask(int idx, int ans = 0) {while (idx) ans += BIT[idx], idx -= idx & -idx; return ans;}
    inline int query_range_sum(int qL, int qR) {return ask(qR+1) - ask(qL);}
} BIT(maxn);

vector<vector<int>> adjA, adjB;
vector<int> parA, parB, szB, heavyB, dfnB, headB;

void dfsB1(int now) {
    for (int x : adjB[now]) {
        dfsB1(x), szB[now] += szB[x];
        if (heavyB[now] == -1 or szB[x] > szB[heavyB[now]]) heavyB[now] = x;
    }
}

void dfsB2(int now, int head) {
    static int tok = 0;
    dfnB[now] = tok++, headB[now] = head;
    if (~heavyB[now]) dfsB2(heavyB[now], head);
    for (int x : adjB[now]) {
        if (x != heavyB[now]) dfsB2(x, x);
    }
}

int query_ancestor_sum(int qX, int ans = 0) {
    while (~qX) {
        ans += BIT.query_range_sum(dfnB[headB[qX]], dfnB[qX]);
        qX = parB[headB[qX]];
    }
    return ans;
}

void dfsA(auto &ops, auto &queries, auto &ans, int now) {
    for (auto &[x, val] : ops[now]) BIT.modify_point_add(dfnB[x], val);
    for (auto &[x, id] : queries[now]) ans[id] = query_ancestor_sum(x);
    for (int x : adjA[now]) dfsA(ops, queries, ans, x);
    for (auto &[x, val] : ops[now]) BIT.modify_point_add(dfnB[x], -val);
}

void solve() {
    int N; cin >> N;
    
    adjA.assign(N, {}), parA.assign(N, -1);
    for (int i = 1; i < N; ++i) cin >> parA[i], --parA[i], adjA[parA[i]].eb(i);
    
    int M; cin >> M;
    
    adjB.assign(M, {}), parB.assign(M, -1);
    for (int i = 1; i < M; ++i) cin >> parB[i], --parB[i], adjB[parB[i]].eb(i);
    
    int K; cin >> K;
    
    vector<vector<pii>> conn(N);
    for (int i = 0, a, b, c; i < K; ++i) cin >> a >> b >> c, conn[a-1].eb(b-1, c);
    
    int Q; cin >> Q;
    
    vector<vector<pii>> queries(N);
    for (int i = 0, a, b; i < Q; ++i) cin >> a >> b, queries[a-1].eb(b-1, i);
    
    /// do HLD on B ///
    
    szB.assign(M, 1), heavyB.assign(M, -1), dfsB1(0);
    dfnB.assign(M, 0), headB.assign(M, -1), dfsB2(0, 0);
    
    /// find dfs order of A ///
    
    vector<int> ans(Q, -1);
    dfsA(conn, queries, ans, 0);
    
    for (int i = 0; i < Q; ++i) cout << ans[i] << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
