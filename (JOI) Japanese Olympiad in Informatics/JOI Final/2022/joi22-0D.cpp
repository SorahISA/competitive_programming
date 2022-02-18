#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define ee emplace
#define eb emplace_back
#define ef push_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    cerr << "\u001b[33m" << "At func " << __FUNCTION__ << ", line " << __LINE__ << ": ",\
    cerr << "(" << #__VA_ARGS__ << ") = ",\
    _do(__VA_ARGS__),\
    cerr << "\u001b[0m"
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}
void chminmax(pii &lhs, pii rhs) {chmin(lhs.X, rhs.X), chmax(lhs.Y, rhs.Y);}

const int INF = INT_MAX;
const int lgmx = 17 + 1;
const int maxn = 1 << 17;

vector<int> tag_mx(maxn<<1, -1), tag_mn(maxn<<1, maxn);
vector<int> L(maxn), R(maxn), dis(maxn);
vector<vector<pii>> jump(lgmx, vector<pii>(maxn, {maxn, -1}));
vector<vector<pii>> seg(lgmx, vector<pii>(maxn<<1, {maxn, -1}));

void seg_modify_range_max(int qL, int qR, int val, int now = 1, int nL = 0, int nR = maxn-1) {
    if (qL <= nL and nR <= qR) return chmax(tag_mx[now], val), void();
    
    int nM = (nL + nR) >> 1;
    if (qL <= nM) seg_modify_range_max(qL, qR, val, now<<1,   nL,   nM);
    if (qR >  nM) seg_modify_range_max(qL, qR, val, now<<1|1, nM+1, nR);
}

void seg_modify_range_min(int qL, int qR, int val, int now = 1, int nL = 0, int nR = maxn-1) {
    if (qL <= nL and nR <= qR) return chmin(tag_mn[now], val), void();
    
    int nM = (nL + nR) >> 1;
    if (qL <= nM) seg_modify_range_min(qL, qR, val, now<<1,   nL,   nM);
    if (qR >  nM) seg_modify_range_min(qL, qR, val, now<<1|1, nM+1, nR);
}

void seg_push_tags() {
    for (int i = 1; i < maxn; ++i) {
        chmax(tag_mx[i<<1], tag_mx[i]), chmax(tag_mx[i<<1|1], tag_mx[i]);
        chmin(tag_mn[i<<1], tag_mn[i]), chmin(tag_mn[i<<1|1], tag_mn[i]);
    }
}

void seg_build() {
    for (int i = 0; i < maxn; ++i) tag_mx[i+maxn] = tag_mn[i+maxn] = i;
}

pii jump_query_range_minmax(int lay, pii q, int now = 1, int nL = 0, int nR = maxn-1) {
    if (q.X <= nL and nR <= q.Y) return seg[lay][now];
    
    int nM = (nL + nR) >> 1;
    pii ans = q;
    if (q.X <= nM) chminmax(ans, jump_query_range_minmax(lay, q, now<<1,   nL,   nM));
    if (q.Y >  nM) chminmax(ans, jump_query_range_minmax(lay, q, now<<1|1, nM+1, nR));
    return ans;
}

void jump_build() {
    for (int i = 0; i < maxn; ++i) seg[0][i+maxn] = jump[0][i] = {tag_mn[i+maxn], tag_mx[i+maxn]};
    for (int lay = 0; lay < lgmx; ++lay) {
        if (lay) {
            for (int i = 0; i < maxn; ++i) {
                seg[lay][i+maxn] = jump[lay][i] = jump_query_range_minmax(lay-1, jump[lay-1][i]);
            }
        }
        for (int i = maxn-1; i >= 1; --i) {
            chminmax(seg[lay][i], seg[lay][i<<1]), chminmax(seg[lay][i], seg[lay][i<<1|1]);
        }
    }
}

void solve() {
    int N, K, M; cin >> N >> K >> M, seg_build();
    
    vector<pii> train(M);
    for (auto &[u, v] : train) {
        cin >> u >> v, --u, --v;
        if (u < v) seg_modify_range_max(u, u+K-1, v);
        if (u > v) seg_modify_range_min(u-K+1, u, v);
    }
    seg_push_tags();
    jump_build();
    
    // for (int lay = 0; lay <= 3; ++lay) {
        // for (int i = 0; i < 8; ++i) debug(lay, i, jump[lay][i].X, jump[lay][i].Y);
    // }
    
    int Q; cin >> Q;
    
    vector<pii> query(Q);
    for (auto &[s, t] : query) {
        cin >> s >> t, --s, --t;
        int ans = 0;
        pii now = {s, s}, tmp;
        for (int lay = lgmx-1; lay >= 0; --lay) {
            tmp = jump_query_range_minmax(lay, now);
            // debug(lay, now.X, now.Y, tmp.X, tmp.Y);
            if (tmp.X > t or tmp.Y < t) chminmax(now, tmp), ans += 1 << lay;
        }
        cout << (ans < N ? ans+1 : -1) << "\n";
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
