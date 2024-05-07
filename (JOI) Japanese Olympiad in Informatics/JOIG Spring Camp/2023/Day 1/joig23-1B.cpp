#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

void solve() {
    int N; cin >> N;
    
    vector<vector<pii>> teleport(N);
    for (int i = 0; i < N-1; ++i) {
        int Ai; cin >> Ai;
        for (int j = 0; j < Ai; ++j) {
            int Pij, Qij; cin >> Pij >> Qij, --Pij, --Qij;
            teleport[Pij].eb(Qij, i);
            teleport[Qij].eb(Pij, i);
        }
    }
    
    vector<int> dis(N, N), vis(N, 0);
    deque<int> que{N-1}; dis[N-1] = 0;
    while (SZ(que)) {
        int now = que[0]; que.pf();
        vis[now] = 1;
        for (auto [ano, room] : teleport[now]) {
            if (vis[ano] and chmin(dis[room], dis[now] + 1)) que.eb(room);
        }
    }
    cout << (dis[0] == N ? -1 : dis[0]) << "\n";
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
