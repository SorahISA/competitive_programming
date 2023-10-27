#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

const int maxn = 100;
const int INF = 100'000;

struct MCMF {
    struct Edge {
        int fr, to, cap, flow, cost, rev;
    } *past[maxn];
    
    vector<Edge> G[maxn];
    bitset<maxn> inq;
    int dis[maxn], up[maxn], s, t, mx, n;
    bool Bellman_Ford(int &flow, int &cost) {
        fill_n(dis, n, INF);
        queue<int> q;
        q.ee(s), inq.reset(), inq[s] = 1;
        up[s] = mx - flow, past[s] = 0, dis[s] = 0;
        while (SZ(q)) {
            int u = q.front(); q.pop(), inq[u] = 0;
            if (!up[u]) continue;
            for (auto &e : G[u]) {
                if (e.flow != e.cap and chmin(dis[e.to], dis[u] + e.cost)) {
                    past[e.to] = &e;
                    up[e.to] = min(up[u], e.cap - e.flow);
                    if (!inq[e.to]) inq[e.to] = 1, q.ee(e.to);
                }
            }
        }
        if (dis[t] == INF) return 0;
        flow += up[t], cost += up[t] * dis[t];
        for (int i = t; past[i]; i = past[i]->fr) {
            auto &e = *past[i];
            e.flow += up[t], G[e.to][e.rev].flow -= up[t];
        }
        return 1;
    }
    
    int mcmf(int _s, int _t, int &cost) {
        s = _s, t = _t, cost = 0;
        int flow = 0;
        while (Bellman_Ford(flow, cost));
        return flow;
    }
    
    void init(int _n, int _mx) {
        n = _n, mx = _mx;
        for (int i = 0; i < n; ++i) G[i].clear();
    }
    
    void add_edge(int a, int b, int cap, int cost) {
        G[a].eb(a, b, cap, 0, cost, SZ(G[b]));
        G[b].eb(b, a, 0, 0, -cost, SZ(G[a]) - 1);
    }
};

void solve() {
    int N; cin >> N;
    
    vector<int> A(N);
    int sum = 0;
    for (int &x : A) cin >> x, sum += x;
    
    vector cost(N, vector<int>(N));
    for (auto &vec : cost) for (int &x : vec) cin >> x;
    
    if (sum % 2 == 1) return cout << -1 << "\n", void();
    
    int ans = INF;
    MCMF mcmf;
    for (int mask = 0; mask < (1<<N); ++mask) {
        mcmf.init(2*N + 2, INF);
        const int st = 0, ed = 2*N + 1;
        for (int i = 0; i < N; ++i) {
            int lcap = (A[i] + (mask >> i & 1)) / 2;
            mcmf.add_edge(st, i+1, lcap, 0);
            mcmf.add_edge(N+i+1, ed, A[i] - lcap, 0);
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                mcmf.add_edge(i+1, j+N+1, INF, cost[i][j]);
            }
        }
        if (int c; mcmf.mcmf(st, ed, c) == sum / 2) chmin(ans, c);
    }
    cout << (ans == INF ? -1 : ans) << "\n";
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i = 1; i <= t; ++i) solve();
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
// #define double __float80
using pii = pair<int, int>;
template <typename T> using MaxHeap = std::priority_queue<T>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)

#ifdef local
#define IOS() void()
#define debug(...) \
    fprintf(stderr, "%sAt [%s], line %d: (%s) = ", "\u001b[33m", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), fprintf(stderr, "%s", "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#define debug(...) void()
#define endl '\n'
#endif

// mt19937_64 rng(steady::chrono_clock::now().time_since_epoch().count());

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

#endif
