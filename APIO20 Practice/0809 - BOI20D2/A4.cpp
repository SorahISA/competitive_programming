#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
// #define double long double
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
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

const int INF = 1LL << 40;
const int maxn = 1E5 + 5;

int tmpans, fl;
vector<pii> adj[maxn]; // (id, sum)
vector<int> p(maxn), minAns(maxn, INF), ans(maxn);
vector<int> col(maxn), vis(maxn), srch(maxn);

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
void U(int x, int y) {p[R(x)] = R(y);}

void dfs_clear(int now) {
    col[now] = vis[now] = 0;
    for (auto [id, sum] : adj[now]) {
        if (vis[id]) dfs_clear(id);
    }
}

void dfs_copy(int now) {
    ans[now] = col[now], vis[now] = 0;
    for (auto [id, sum] : adj[now]) {
        if (vis[id]) dfs_copy(id);
    }
}

void dfs(int now) {
    tmpans += abs(col[now]), vis[now] = 1;
    if (tmpans > INF) {fl = 0; return;}
    for (auto [id, sum] : adj[now]) {
        if (!fl) return;
        if (!vis[id]) col[id] = sum - col[now], dfs(id);
        if (col[id] != sum - col[now]) {fl = 0; return;}
    }
}

int32_t main() {
    fastIO();
    iota(ALL(p), 0);
    
    int n, m;
    cin >> n >> m;
    
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        cin >> u >> v >> w, U(u, v), w *= 2;
        adj[u].eb(v, w), adj[v].eb(u, w);
    }
    
    vector<int> deg(n);
    iota(ALL(deg), 1);
    sort(ALL(deg), [](auto a, auto b) {return adj[a].size() > adj[b].size();});
    
    for (auto i : deg) {
        if (++srch[R(i)] <= 20) {
            for (int val = -1; val <= 4; ++val) {
                dfs_clear(i);
                tmpans = 0, fl = 1, col[i] = val, dfs(i);
                // for (int j = 1; j <= n; ++j) cout << col[j] << "|";
                // if (fl) cout << " YES"; cout << "\n";
                if (fl and tmpans < minAns[R(i)]) minAns[R(i)] = tmpans, dfs_copy(i);
            }
        }
    }
    
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += minAns[R(i)];
        minAns[R(i)] = 0;
    }
    
    if (sum >= INF) cout << "NO\n";
    else {
        cout << "YES\n";
        for (int i = 1; i <= n; ++i) {
            cout << fixed << setprecision(1) << ans[i] / 2.0 << " \n"[i == n];
        }
    }
    
    return 0;
}
