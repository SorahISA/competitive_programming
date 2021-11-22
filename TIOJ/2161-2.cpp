#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ef push_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) (int)(x).size()
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

const int maxn = 1 << 18;

namespace SegTree {

vector<int> tag(maxn<<1, -1), sum(maxn<<1, 0);

void Pull(int now) {
    sum[now] = sum[now<<1] + sum[now<<1|1];
}

void Push(int now, int len) {
    if (tag[now] == -1) return;
    tag[now<<1] = tag[now<<1|1] = tag[now];
    sum[now<<1] = sum[now<<1|1] = (len >> 1) * tag[now];
    tag[now] = -1;
}

void RangeModify(int qL, int qR, int val, int now = 1, int nL = 0, int nR = maxn-1) {
    if (qR < nL or nR < qL) return;
    if (qL <= nL and nR <= qR) {
        tag[now] = val;
        sum[now] = (nR - nL + 1) * val;
        return;
    }
    
    int nM = (nL + nR) >> 1;
    Push(now, nR - nL + 1);
    RangeModify(qL, qR, val, now << 1,     nL,     nM);
    RangeModify(qL, qR, val, now << 1 | 1, nM + 1, nR);
    Pull(now);
}

int RangeSum(int qL, int qR, int now = 1, int nL = 0, int nR = maxn-1) {
    if (qR < nL or nR < qL) return 0;
    if (qL <= nL and nR <= qR) return sum[now];
    
    int nM = (nL + nR) >> 1, ans = 0;
    Push(now, nR - nL + 1);
    ans += RangeSum(qL, qR, now << 1,     nL,     nM);
    ans += RangeSum(qL, qR, now << 1 | 1, nM + 1, nR);
    Pull(now);
    return ans;
}

void build(int N, vector<pii> &par, vector<int> &inv) {
    for (int i = 2; i <= N; ++i) sum[i+maxn] = par[inv[i]].Y;
    for (int i = maxn-1; i >= 1; --i) sum[i] = sum[i<<1] + sum[i<<1|1];
}

};

namespace HLD {

int dfn_tok = 0;
vector<pii> adj[maxn], par(maxn); /// (id, val)
vector<int> head(maxn), dep(maxn), dfn(maxn), inv(maxn), sz(maxn, 1), heavy(maxn);

void dfs1(int now, int lst = -1) {
    for (auto [x, val] : adj[now]) {
        if (x == lst) continue;
        par[x] = pii{now, val};
        dep[x] = dep[now] + 1;
        dfs1(x, now), sz[now] += sz[x];
        if (!heavy[now] or sz[x] > sz[heavy[now]]) heavy[now] = x; 
    }
}

void dfs2(int now, int hd, int lst = -1) {
    dfn[now] = ++dfn_tok, inv[dfn_tok] = now, head[now] = hd;
    if (heavy[now]) dfs2(heavy[now], hd, now);
    for (auto [x, val] : adj[now]) {
        if (x == heavy[now] or x == lst) continue;
        dfs2(x, x, now);
    }
}

vector<pii> decomposite(int u, int v) {
    vector<pii> ret;
    while (head[u] != head[v]) {
        if (dep[head[u]] < dep[head[v]]) swap(u, v);
        ret.eb(dfn[head[u]], dfn[u]), u = par[head[u]].X;
    }
    if (dfn[u] > dfn[v]) swap(u, v);
    if (u != v) ret.eb(dfn[u] + 1, dfn[v]);
    return ret;
}

void init(int N, int root) {
    for (int i = 0; i < N-1; ++i) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].eb(v, w), adj[v].eb(u, w);
    }
    dfs1(root);
    dfs2(root, root);
}

};

void solve() {
    int N, Q; cin >> N >> Q;
    
    HLD::init(N, 1);
    SegTree::build(N, HLD::par, HLD::inv);
    
    // for (int i = 1; i <= N; ++i) {
        // cerr << i << ": " << HLD::dfn[i] << " " << HLD::head[i] << " " << HLD::par[i].X << " " << HLD::par[i].Y << "\n";
    // }
    
    while (Q--) {
        int ans = 0, u, v; cin >> u >> v;
        for (auto [L, R] : HLD::decomposite(u, v)) {
            // cerr << Q << ": " << L << " " << R << "\n";
            // for (int i = L; i <= R; ++i) {
                // ans += HLD::par[HLD::inv[i]].Y;
                // HLD::par[HLD::inv[i]].Y = 0;
            // }
            ans += SegTree::RangeSum(L, R);
            SegTree::RangeModify(L, R, 0);
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

/*
14 5
1 2 1
2 3 2
3 4 4
4 5 8
5 6 16
3 7 32
7 8 64
8 9 128
7 10 256
2 11 512
11 12 1024
12 13 2048
11 14 4096
10 12
1 8
6 13
5 10
9 14

1826
65
2076
0
4224
*/
