#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int INF = LLONG_MAX >> 2;

void solve() {
    int N, M; cin >> N >> M;
    int S, T, L, K; cin >> S >> T >> L >> K, --S, --T;
    
    vector<vector<pii>> adj(N);
    for (int i = 0; i < M; ++i) {
        int a, b, c; cin >> a >> b >> c, --a, --b;
        adj[a].eb(b, c), adj[b].eb(a, c);
    }
    
    auto Dijkstra = [&](int st) -> vector<int> {
        vector<int> dis(N, INF); dis[st] = 0;
        prior<pii> pq; pq.ee(dis[st], st);
        while (SZ(pq)) {
            auto [_d, now] = pq.top(); pq.pop();
            if (_d != dis[now]) continue;
            for (auto [x, cost] : adj[now]) { if (chmin(dis[x], _d + cost)) pq.ee(dis[x], x); }
        }
        return dis;
    };
    
    auto dis_S = Dijkstra(S);
    auto dis_T = Dijkstra(T);
    
    if (dis_S[T] <= K) { cout << N * (N-1) / 2 << "\n"; return; }
    
    sort(ALL(dis_S)), sort(ALL(dis_T));
    
    int ans = 0;
    for (int i = 0, j = N-1; i < N; ++i) {
        while (j >= 0 and dis_S[i] + dis_T[j] + L > K) --j;
        ans += j + 1;
    }
    cout << ans << "\n";
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
