// #pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
// template <typename T>
// using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(0, 1); \
                 auto rnd = bind(__dis, __gen);

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 1E5 + 5;

vector<pii> adj[maxn];
vector<int> dis, vis;
prior<pii> pq;

void dijkstra(int now) {
    vis[now] = 1;
    for (auto [id, dist] : adj[now]) {
        if (dis[now] + dist < dis[id]) pq.push({dis[id] = dis[now] + dist, id});
    }
    
    while (!pq.empty()) {
        auto [dist, id] = pq.top(); pq.pop();
        if (vis[id]) continue;
        dijkstra(id);
    }
}

int32_t main() {
    fastIO();
    
    int n, m, u, v, w;
    cin >> n >> m, dis.assign(n, INF), vis.assign(n, 0);
    
    while (m--) cin >> u >> v >> w, --u, --v, adj[u].eb(v, w), adj[v].eb(u, w);
    
    dis[0] = 0, dijkstra(0);
    
    cout << *max_element(ALL(dis)) << "\n";
    
    return 0;
}
