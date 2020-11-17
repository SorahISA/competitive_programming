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

int n, cnt1 = 0, cnt2 = 0;
vector<int> ans1, ans2;
vector<int> adj[maxn], par(maxn), sz(maxn), pl(maxn);
deque<int> deq;

void dfs(int now, int lst) {
    par[now] = lst;
    for (auto x : adj[now]) {
        if (x != lst) dfs(x, now);
    }
    if (now != 1 and pl[now] == now) ++cnt1, swap(pl[now], pl[par[now]]);
}

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

void solve1() {
    iota(ALL(pl), 0);
    
    dfs(1, -1);
    
    if (pl[1] == 1) ++cnt1, swap(pl[1], pl[adj[1][0]]);
    
    cnt1 *= 2, ans1 = vector<int>(pl.begin()+1, pl.begin()+n+1);
}

void solve2() {
    iota(ALL(pl), 0);
    
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
    
    for (int i = 1; i <= n; ++i) cnt2 += min(sz[i], n - sz[i]);
    
    cnt2 *= 2, ans2 = vector<int>(pl.begin()+1, pl.begin()+n+1);
}

int32_t main() {
    fastIO();
    
    cin >> n;
    
    for (int i = 0; i < n-1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].eb(v), adj[v].eb(u);
    }
    
    solve1(), solve2();
    
    cout << cnt1 << " " << cnt2 << "\n";
    for (auto x : ans1) cout << x << " "; cout << "\n";
    for (auto x : ans2) cout << x << " "; cout << "\n";
    
    return 0;
}
