#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

struct SegTree {
    
    vector<int> sum, tag;
    int maxn;
    
    void init(int N) {
        maxn = (1 << (__lg(N+1) + 1));
        sum.assign(2*maxn, 0);
        tag.assign(2*maxn, 0);
    }
    
    void push(int now, int len) {
        int lt = now << 1, rt = lt | 1;
        tag[lt] += tag[now], sum[lt] += tag[now] * (len >> 1);
        tag[rt] += tag[now], sum[rt] += tag[now] * (len >> 1);
        tag[now] = 0;
    }
    
    void pull(int now) {
        int lt = now << 1, rt = lt | 1;
        sum[now] = sum[lt] + sum[rt];
    }
    
    void modify_range_add(int qL, int qR, int val) { modify_range_add(qL, qR, val, 1, 0, maxn-1); }
    void modify_range_add(int qL, int qR, int val, int now, int nL, int nR) {
        if (qL <= nL and nR <= qR) {
            tag[now] += val;
            sum[now] += val * (nR - nL + 1);
            return;
        }
        
        push(now, nR-nL+1);
        
        int nM = (nL + nR) >> 1;
        if (qL <= nM) modify_range_add(qL, qR, val, now<<1,   nL,   nM);
        if (nM <  qR) modify_range_add(qL, qR, val, now<<1|1, nM+1, nR);
        
        pull(now);
    }
    
    int query_range_sum(int qL, int qR) { return query_range_sum(qL, qR, 1, 0, maxn-1); }
    int query_range_sum(int qL, int qR, int now, int nL, int nR) {
        if (qL <= nL and nR <= qR) return sum[now];
        
        push(now, nR-nL+1);
        
        int nM = (nL + nR) >> 1, ans = 0;
        if (qL <= nM) ans += query_range_sum(qL, qR, now<<1,   nL,   nM);
        if (nM <  qR) ans += query_range_sum(qL, qR, now<<1|1, nM+1, nR);
        
        return ans;
    }
    
};

void solve() {
    int N, D; cin >> N >> D;
    
    vector<int> C(N+1);
    for (int i = 1; i <= N; ++i) cin >> C[i];
    C[0] = -2 * N * D;
    
    vector<int> diff(N+1, 0);
    for (int i = 1; i <= N; ++i) diff[i] = ((C[i] - C[i-1]) % D + D) % D;
    
    vector<int> pre(N+1);
    partial_sum(ALL(C), begin(pre));
    
    int Q; cin >> Q;
    
    vector<vector<pii>> queries(N+1);
    for (int q = 0; q < Q; ++q) {
        int L, R; cin >> L >> R;
        queries[R].eb(L, q);
    }
    
    vector<int> ans(Q);
    SegTree seg; seg.init(N);
    deque<tuple<int, int, int, int>> deq; /// (l, r, bl, br)
    deq.eb(0, 0, C[0], C[0]);
    for (int R = 1; R <= N; ++R) {
        int now_b = C[R], now_r = R;
        auto [l, r, bl, br] = deq.back();
        seg.modify_range_add(now_r, now_r, now_b);
        while (br > now_b - diff[now_r]) {
            seg.modify_range_add(l, r, now_b - diff[now_r] - br);
            now_b = bl + (now_b - diff[now_r] - br), now_r = l;
            deq.pb(), tie(l, r, bl, br) = deq.back();
            // debug(now_b, now_r, l, r, bl, br, now_b - diff[now_r]);
            // assert(SZ(deq));
        }
        deq.eb(now_r, R, now_b, C[R]);
        
        for (auto [L, qid] : queries[R]) {
            if (seg.query_range_sum(L, L) < 0) ans[qid] = -1;
            else ans[qid] = (pre[R] - pre[L-1] - seg.query_range_sum(L, R)) / D;
        }
        
        // for (auto [_l, _r, _bl, _br] : deq) debug(_l, _r, _bl, _br);
        // for (int i = 1; i <= R; ++i) debug(i, R, seg.query_range_sum(i, i));
    }
    
    for (int x : ans) cout << x << "\n";
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

using i64 = long long;
#define int i64
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define ee emplace
#define eb emplace_back
#define pb pop_back
#define ef emplace_front
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
