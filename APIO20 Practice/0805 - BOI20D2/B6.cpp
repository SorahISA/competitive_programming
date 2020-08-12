#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
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

const int maxn = 1E5 + 5;

vector<int> adj[maxn], par(maxn), sz(maxn), pl(maxn);
deque<int> deq;

void dfs_sz(int now, int lst) {
    sz[now] = 1, par[now] = lst;
    for (auto x : adj[now]) {
        if (x != lst) dfs_sz(x, now), sz[now] += sz[x];
    }
}

void dfs_get(int now, int lst) {
    deq.push_back(now);
    for (auto x : adj[now]) {
        if (x != lst) dfs_get(x, now);
    }
}

void dfs_put(int now, int lst) {
    pl[now] = deq.front(), deq.pop_front();
    for (auto x : adj[now]) {
        if (x != lst) dfs_put(x, now);
    }
}

int32_t main() {
    fastIO();
    iota(ALL(pl), 0);
    
    int n, u, v, cnt = 0;
    cin >> n;
    
    for (int i = 0; i < n-1; ++i) {
        cin >> u >> v, adj[u].eb(v), adj[v].eb(u);
    }
    
    dfs_sz(1, -1);
    
    int rt = 0;
    for (int i = 1; i <= n; ++i) {
        int maxCh = 0;
        for (auto x : adj[i]) {
            if (x != par[i]) maxCh = max(maxCh, sz[x]);
            else             maxCh = max(maxCh, n - sz[i]);
        }
        if (maxCh <= n/2) {rt = i; break;}
    }
    
    dfs_sz(rt, -1);
    sort(ALL(adj[rt]), [](auto a, auto b) {return sz[a] > sz[b];});
    
    int rt_ch = adj[rt].size();
    for (int i = 0; i < rt_ch; ++i) dfs_get(adj[rt][i], rt);
    for (int i = 1; i < rt_ch; ++i) dfs_put(adj[rt][i], rt);
    pl[rt] = deq.front(), deq.pop_front();
    deq.push_back(rt), dfs_put(adj[rt][0], rt);
    
    for (int i = 1; i <= n; ++i) cnt += min(sz[i], n - sz[i]);
    
    cout << cnt * 2 << "\n";
    for (int i = 1; i <= n; ++i) cout << pl[i] << " \n"[i == n];
    
    return 0;
}