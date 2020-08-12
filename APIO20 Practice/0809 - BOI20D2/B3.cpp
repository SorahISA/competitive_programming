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

int cnt = 0;
vector<int> adj[maxn], par(maxn), pl(maxn);

void dfs(int now, int lst) {
    par[now] = lst;
    for (auto x : adj[now]) {
        if (x != lst) dfs(x, now);
    }
    if (now != 1 and pl[now] == now) ++cnt, swap(pl[now], pl[par[now]]);
}

int32_t main() {
    fastIO();
    iota(ALL(pl), 0);
    
    int n, u, v;
    cin >> n;
    
    for (int i = 0; i < n-1; ++i) {
        cin >> u >> v, adj[u].eb(v), adj[v].eb(u);
    }
    
    dfs(1, -1);
    
    if (pl[1] == 1) ++cnt, swap(pl[1], pl[adj[1][0]]);
    
    cout << cnt * 2 << "\n";
    for (int i = 1; i <= n; ++i) cout << pl[i] << " \n"[i == n];
    
    return 0;
}
