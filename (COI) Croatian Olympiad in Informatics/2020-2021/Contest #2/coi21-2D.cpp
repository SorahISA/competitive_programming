#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

const int maxn = 1E5 + 5;

int ans = 0;
vector<int> adj[maxn], val(maxn), deg(maxn), vis(maxn), p(maxn), maxV(maxn);

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
void U(int x, int y) {x = R(x), y = R(y); maxV[y] = max(maxV[y], maxV[x]), p[x] = y;}

int32_t main() {
    fastIO();
    
    int n;
    cin >> n, iota(ALL(p), 0);
    
    vector<pii> pq;
    
    for (int i = 1; i <= n; ++i) cin >> val[i], maxV[i] = val[i], pq.eb(val[i], i);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        adj[u].eb(v), adj[v].eb(u), ++deg[u], ++deg[v];
    }
    sort(ALL(pq), [](auto p1, auto p2) {return p1.X > p2.X;});
    
    for (int i = 0; i < n; ++i) {
        int id = pq[i].Y;
        ans += deg[id] * val[id];
        for (auto x : adj[id]) --deg[x];
    }
    
    // cout << ans << "\n";
    
    for (int i = n-1; i >= 0; --i) {
        int id = pq[i].Y; vis[id] = 1;
        for (auto x : adj[id]) {
            if (i != n-1 and vis[x]) ans += maxV[R(x)];
            if (vis[x]) U(id, x);
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
