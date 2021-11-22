#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

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

const int maxn = 50000 + 5;
const int lgmx = 16 + 1;

struct Edge {
    int to, dis, st, ed, gap;
    Edge(int _to, int _dis, int _st, int _ed, int _gap) :
        to(_to), dis(_dis), st(_st), ed(_ed), gap(_gap) {}
};

vector<Edge> adj[maxn];
int dep[maxn];
int anc[2][maxn][lgmx][61]; /// anc[][][][60] for parent
/// anc[0][i][j][t] means how many minutes it takes to take you to anc[0][i][j][60] when you just arrive station i at t minute ///

void dfs(int now, int lst) {
    for (auto eg : adj[now]) {
        if (eg.to == lst) continue;
        dep[eg.to] = dep[now] + 1;
        anc[0][eg.to][0][60] = anc[1][eg.to][0][60] = now;
        for (int i = 0; i < 60; ++i) {
            anc[0][eg.to][0][i] = eg.gap - (i + eg.gap - eg.ed) % eg.gap + eg.dis;
            anc[1][eg.to][0][i] = eg.gap - (i + eg.gap - eg.st) % eg.gap + eg.dis;
        }
        dfs(eg.to, now);
    }
}

int lca(int x, int y, int t) {
    /// x -> lca use anc[0][][][] ///
    /// lca -> y use anc[1][][][] ///
    int cost = 0;
    deque<pii> store_query; /// stores queries lca -> y (anc[][o][][], anc[][][o][])
    for (int i = lgmx-1; i >= 0; --i) {
        if (dep[anc[0][x][i][60]] >= dep[y]) {
            // cout << "(" << anc[0][x][i][60] << "," << dep[anc[0][x][i][60]] << ") ";
            // cout << "x: " << i << ", ";
            cost += anc[0][x][i][t%60];
            t += anc[0][x][i][t%60];
            x = anc[0][x][i][60];
        }
        else if (dep[anc[1][y][i][60]] >= dep[x]) {
            // cout << "y: " << i << ", ";
            store_query.push_back({y, i});
            y = anc[1][y][i][60];
        }
    }
    if (x == y) {
        while (!store_query.empty()) {
            pii q = store_query.back(); store_query.pop_back();
            cost += anc[1][q.X][q.Y][t%60];
            t += anc[1][q.X][q.Y][t%60];
        }
        return cost - 1;
    }
    for (int i = lgmx-1; i >= 0; --i) {
        if (anc[0][x][i][60] != anc[1][y][i][60]) {
            // cout << "xy: " << i << ", ";
            cost += anc[0][x][i][t%60];
            t += anc[0][x][i][t%60];
            x = anc[0][x][i][60];
            store_query.push_back({y, i});
            y = anc[0][y][i][60];
        }
    }
    cost += anc[0][x][0][t%60];
    t += anc[0][x][0][t%60];
    x = anc[0][x][0][60];
    store_query.push_back({y, 0});
    y = anc[0][y][0][60];
    while (!store_query.empty()) {
        pii q = store_query.back(); store_query.pop_back();
        cost += anc[1][q.X][q.Y][t%60];
        t += anc[1][q.X][q.Y][t%60];
    }
    return cost - 1;
}

void build(int n) {
    for (int lay = 1; lay < lgmx; ++lay) {
        for (int i = 1; i <= n; ++i) {
            int par = anc[0][i][lay-1][60];
            anc[0][i][lay][60] = anc[1][i][lay][60] = anc[0][par][lay-1][60];
            for (int j = 0; j < 60; ++j) {
                int landing_0 = anc[0][i][lay-1][j] + j;
                anc[0][i][lay][j] = anc[0][i][lay-1][j] + anc[0][par][lay-1][landing_0%60];
                int landing_1 = anc[1][par][lay-1][j] + j;
                anc[1][i][lay][j] = anc[1][par][lay-1][j] + anc[1][i][lay-1][landing_1%60];
            }
        }
    }
}

void solve() {
    int n, q; cin >> n >> q;
    
    for (int i = 0; i < n-1; ++i) {
        int u, v, w, a, b, p;
        cin >> u >> v >> w >> a >> b >> p;
        adj[u].eb(v, w, a, b, p);
        adj[v].eb(u, w, b, a, p);
    }
    
    dep[0] = -1, dfs(1, -1), build(n);
    
    // for (int i = 1; i <= n; ++i) cout << dep[i] << " \n"[i == n];
    // for (int i = 1; i <= n; ++i) cout << "(" << anc[0][i][0][0] << "," << anc[0][i][0][60] << ")" << " \n"[i == n];
    // for (int i = 1; i <= n; ++i) cout << "(" << anc[1][i][0][0] << "," << anc[1][i][0][60] << ")" << " \n"[i == n];
    
    // for (int i = 0; i < 60; ++i) cout << anc[1][2][0][i] << " \n"[i == 59];
    // for (int i = 0; i < 60; ++i) cout << anc[1][3][0][i] << " \n"[i == 59];
    // for (int i = 0; i < 60; ++i) cout << anc[1][3][1][i] << " \n"[i == 59];
    
    while (q--) {
        int h, m, x, y;
        cin >> h >> m >> x >> y, m = (m + 59) % 60;
        cout << lca(x, y, m) << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}

/*
5 6
1 2 5 1 0 3
2 3 40 5 4 6
2 4 100 0 0 1
4 5 1000 2 1 3
0 17 1 3
0 37 4 5
0 4 5 1
0 59 3 5
0 38 4 5
0 40 4 5

52
1001
1108
1147
1000
1001
*/