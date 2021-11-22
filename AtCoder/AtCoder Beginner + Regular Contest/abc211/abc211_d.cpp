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
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxn = 2E5 + 5;
const int mod = 1E9 + 7;

vector<int> adj[maxn], dis(maxn, -1), ans(maxn, 0);
vector<pii> edges[maxn]; /// edges[i] stores out edges from level i to level (i+1)

void bfs(int st) {
    queue<int> que;
    dis[st] = 0, que.push(st);
    ans[st] = 1;
    
    while (!que.empty()) {
        int now = que.front(); que.pop();
        ans[now] %= mod;
        for (auto x : adj[now]) {
            if (dis[x] == -1) dis[x] = dis[now] + 1, que.push(x);
            if (dis[x] == dis[now] + 1) ans[x] += ans[now];
        }
    }
}

void solve() {
    int N, M; cin >> N >> M;
    
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v;
        adj[u].eb(v), adj[v].eb(u);
    }
    bfs(1);
    
    cout << ans[N] << "\n";
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