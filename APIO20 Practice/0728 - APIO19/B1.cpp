#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

struct Edge {
    int u, v, w;
};

const int maxn = 1000 + 5;

vector<pii> adj[maxn];
vector<int> vis(maxn);

void dfs(int now, int wei, int &cnt, int id) {
    ++cnt, vis[now] = id;
    for (auto x : adj[now]) {
        if (x.Y >= wei and vis[x.X] != id) dfs(x.X, wei, cnt, id);
    }
}

int32_t main() {
    fastIO();
    
    int n, m, q;
    cin >> n >> m;
    
    vector<Edge> edge(m);
    for (auto &e : edge) {
        cin >> e.u >> e.v >> e.w;
        adj[e.u].eb(e.v, e.w);
        adj[e.v].eb(e.u, e.w);
    }
    
    cin >> q;
    
    for (int i = 1; i <= q; ++i) {
        int op, st, wi;
        cin >> op >> st >> wi;
        
        if (op == 1) {
            --st;
            for (auto &x : adj[edge[st].u]) {
                if (x.X == edge[st].v and x.Y == edge[st].w) {x.Y = wi; break;}
            }
            for (auto &x : adj[edge[st].v]) {
                if (x.X == edge[st].u and x.Y == edge[st].w) {x.Y = wi; break;}
            }
            edge[st].w = wi;
        }
        if (op == 2) {
            int cnt = 0;
            dfs(st, wi, cnt, i);
            cout << cnt << "\n";
        }
    }
    
    return 0;
}