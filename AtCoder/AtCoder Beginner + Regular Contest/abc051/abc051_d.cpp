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
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 100 + 5;
const int maxm = 1000 + 5;

vector<pii> adj[maxn];
int vis[maxn], dis[maxn], cnt[maxn][maxn];

void dijkstra(int now) {
    memset(vis, 0x00, sizeof(vis));
    memset(dis, 0x7f, sizeof(dis));
    dis[now] = 0;
    
    prior<pii> pq;
    pq.push({0, now});
    
    while (!pq.empty()) {
        now = pq.top().Y; pq.pop();
        if (vis[now]) continue;
        vis[now] = 1;
        
        for (auto x : adj[now]) {
            if (vis[x.X]) continue;
            if (dis[x.X] > dis[now] + x.Y) pq.push({dis[x.X] = dis[now] + x.Y, x.X});
        }
    }
}

int32_t main() {
    fastIO();
    
    int n, m;
    cin >> n >> m;
    
    vector<int> e1(m), e2(m), e3(m); /// from , to , dis ///
    for (int i = 0; i < m; ++i) {
        cin >> e1[i] >> e2[i] >> e3[i];
        if (e1[i] > e2[i]) swap(e1[i], e2[i]);
        adj[e1[i]].eb(e2[i], e3[i]), adj[e2[i]].eb(e1[i], e3[i]);
    }
    
    for (int i = 1; i <= n; ++i) {
        dijkstra(i);
        for (int j = 0; j < m; ++j) {
            if (abs(dis[e1[j]] - dis[e2[j]]) == e3[j]) ++cnt[e1[j]][e2[j]];
        }
    }
    
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        if (!cnt[e1[i]][e2[i]]) ++ans;
    }
    cout << ans << "\n";
    
    return 0;
}
