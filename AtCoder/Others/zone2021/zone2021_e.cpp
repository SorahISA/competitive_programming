#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % (uint64_t)(R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int INF = INT_MAX;
const int maxn = 500 + 5;

vector<pii> adj[maxn * maxn]; /// (to, cost)
vector<int> dis(maxn * maxn, INF), vis(maxn * maxn, 0);
prior<pii> pq;

void dijkstra(int now) {
    vis[now] = 1;
    for (auto [to, cost] : adj[now]) {
        if (dis[to] > dis[now] + cost) pq.push({dis[to] = dis[now] + cost, to});
    }
    
    while (!pq.empty()) {
        auto [dist, nxt] = pq.top(); pq.pop();
        if (!vis[nxt]) dijkstra(nxt);
    }
}

void solve() {
    int R, C; cin >> R >> C;
    
    for (int i = 1; i <= R; ++i) {
        for (int j = 1; j <= C-1; ++j) {
            int cost; cin >> cost;
            adj[i*maxn+j].eb(i*maxn+j+1, cost);
            adj[i*maxn+j+1].eb(i*maxn+j, cost);
        }
    }
    
    for (int i = 1; i <= R-1; ++i) {
        for (int j = 1; j <= C; ++j) {
            int cost; cin >> cost;
            adj[i*maxn+j].eb((i+1)*maxn+j, cost);
            for (int k = 1; k <= i; ++k) adj[(i+1)*maxn+j].eb((i+1-k)*maxn+j, k+1);
        }
    }
    
    dis[1*maxn+1] = 0, dijkstra(1*maxn+1);
    cout << dis[R*maxn+C] << "\n";
    
    // for (int i = 1; i <= R; ++i) {
        // for (int j = 1; j <= C; ++j) cout << dis[i*maxn+j] << " \n"[j == C];
    // }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}