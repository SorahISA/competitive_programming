// #pragma GCC optimize("Ofast", "unroll-loops")
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
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<class T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxn = 2000 + 5;
const int INF = 1E15;

map<string, int> trans;
vector<pii> adj[maxn];
vector<int> dis(maxn), vis(maxn);

void dijkstra(int st) {
    fill(ALL(dis), INF), dis[st] = 0;
    fill(ALL(vis), 0);
    
    prior<pii> pq; /// (dis, idx)
    pq.push({0, st});
    
    while (!pq.empty()) {
        int now = pq.top().Y; pq.pop();
        if (vis[now]) continue;
        vis[now] = 1;
        for (auto [id, dist] : adj[now]) {
            if (dis[id] > dis[now] + dist) {
                dis[id] = dis[now] + dist;
                pq.push({dis[id], id});
            }
        }
    }
}

void solve() {
    int n, m; cin >> n >> m;
    
    while (m--) {
        string u, v;
        int t;
        static int tok = 0;
        cin >> u >> v >> t;
        if (trans[u] == 0) trans[u] = ++tok;
        if (trans[v] == 0) trans[v] = ++tok;
        adj[trans[u]].eb(trans[v], t);
    }
    
    int q; cin >> q;
    
    while (q--) {
        string u, v; cin >> u >> v;
        dijkstra(trans[u]);
        if (dis[trans[v]] == INF) cout << "Roger\n";
        else cout << dis[trans[v]] << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}