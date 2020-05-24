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

int32_t main() {
    fastIO();
    
    int n, m;
    string str;
    cin >> n >> m;
    
    vector<pii> adj[n+5][m+5];
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> str;
            if (str[0] == '0') adj[i][j].pb({i, j+1});
            if (str[1] == '0') adj[i][j].pb({i+1, j});
            if (str[2] == '0') adj[i][j].pb({i, j-1});
            if (str[3] == '0') adj[i][j].pb({i-1, j});
        }
    }
    
    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    
    vector<vector<int>> dis(n+5, vector<int>(m+5, INF));
    vector<vector<int>> vis(n+5, vector<int>(m+5, 0));
    queue<pii> que; que.push({sx, sy}); dis[sx][sy] = 0;
    
    while (!que.empty()) {
        int nx = que.front().X, ny = que.front().Y; que.pop();
        if (vis[nx][ny]) continue;
        vis[nx][ny] = 1;
        
        for (auto x : adj[nx][ny]) {
            if (dis[x.X][x.Y] > dis[nx][ny] + 1) {
                dis[x.X][x.Y] = dis[nx][ny] + 1; que.push(x);
            }
        }
    }
    
    cout << (dis[tx][ty] == INF ? -1 : dis[tx][ty]) << "\n";
    
    return 0;
}
