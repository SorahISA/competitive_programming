#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

const int INF = 1E15;
const int maxn = 1 << 17;

vector<pii> adj[5*maxn]; /// 0: segL; 2*maxn: segR; 4*maxn: val
vector<int> dis(5*maxn, INF), vis(5*maxn);
vector<int> dcp; /// return value in [decompose]
prior<pii> pq; /// {val, id}

void dijkstra(int now) {
    // cout << __FUNCTION__ << ": " << now << " " << dis[now] << "\n";
    vis[now] = 1;
    for (auto [id, val] : adj[now]) {
        if (dis[id] > dis[now] + val) {
            dis[id] = dis[now] + val;
            pq.push({dis[id], id});
        }
    }
    while (!pq.empty()) {
        auto [val, id] = pq.top(); pq.pop();
        if (vis[id]) continue;
        dijkstra(id);
    }
}

void decompose(int ql, int qr, int now = 1, int l = 0, int r = maxn-1) {
    // cout << __FUNCTION__ << ": " << now << " " << l << " " << r << "\n";
    if (qr < l or r < ql) return;
    if (ql <= l and r <= qr) {dcp.eb(now); return;}
    int lt = now << 1, rt = lt | 1, m = l + r >> 1;
    decompose(ql, qr, lt, l, m), decompose(ql, qr, rt, m+1, r);
}

void solve() {
    int n, q, st; cin >> n >> q >> st;
    for (int i = 1; i < maxn; ++i) {
        adj[i].eb(i<<1, 0);
        adj[i].eb(i<<1|1, 0);
        adj[2*maxn + (i<<1)].eb(2*maxn + i, 0);
        adj[2*maxn + (i<<1|1)].eb(2*maxn + i, 0);
        adj[maxn + i - 1].eb(4*maxn + i - 1, 0);
        adj[4*maxn + i - 1].eb(3*maxn + i - 1, 0);
    }
    
    for (int i = 0; i < q; ++i) {
        int op; cin >> op;
        if (op == 1) {
            int u, v, w; cin >> u >> v >> w;
            adj[4*maxn + u].eb(4*maxn + v, w);
        }
        if (op == 2) {
            int u, l, r, w; cin >> u >> l >> r >> w;
            dcp.clear(), decompose(l, r);
            // for (auto x : dcp) cout << x << " "; cout << "\n";
            for (auto x : dcp) adj[4*maxn + u].eb(x, w);
        }
        if (op == 3) {
            int l, r, v, w; cin >> v >> l >> r >> w;
            dcp.clear(), decompose(l, r);
            // for (auto x : dcp) cout << x << " "; cout << "\n";
            for (auto x : dcp) adj[2*maxn + x].eb(4*maxn + v, w);
        }
    }
    
    dis[4*maxn + st] = 0, dijkstra(4*maxn + st);
    for (int i = 1; i <= n; ++i) {
        cout << (dis[4*maxn + i] == INF ? -1 : dis[4*maxn + i]) << " \n"[i == n];
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}