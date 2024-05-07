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

const int INF = LLONG_MAX >> 2;

void Dijkstra(auto &adj, auto &dis, int st) {
    prior<pii> pq; pq.ee(dis[st], st);
    while (SZ(pq)) {
        auto [_, now] = pq.top(); pq.pop();
        if (dis[now] != _) continue;
        for (auto [x, cost] : adj[now]) {
            if (chmin(dis[x], dis[now] + cost)) pq.ee(dis[x], x);
        }
    }
}

void solve() {
    int N, M; cin >> N >> M;
    
    vector<vector<pii>> adj(N);
    for (int i = 0, a, b, c; i < M; ++i) {
        cin >> a >> b >> c;
        adj[a].eb(b, c), adj[b].eb(a, c);
    }
    
    vector<int> disS(N, INF), disE(N, INF);
    disS[0]   = 0, Dijkstra(adj, disS, 0);
    disE[N-1] = 0, Dijkstra(adj, disE, N-1);
    
    vector<bool> on_sp(N, false);
    for (int i = 0; i < N; ++i) on_sp[i] = (disS[i] + disE[i] == disS[N-1]);
    
    int goal = disS[N-1] - 1, ans = INF;
    for (int i = 0; i < N; ++i) {
        for (auto [x, cost] : adj[i]) {
            // debug(i, x, cost, goal - disS[i] - disE[x]);
            if ((on_sp[i] and on_sp[x]) or disS[i] + disE[x] >= goal) continue;
            chmin(ans, cost - (goal - disS[i] - disE[x]));
        }
    }
    cout << (ans == INF ? -1 : ans) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
