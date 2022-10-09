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

vector<int> adj[maxn], vis(maxn), all_dep;
int maxDep, maxDepID, maxMaxDep;

void dfs(int now) {
    vis[now] = 1;
    for (auto x : adj[now]) {
        if (!vis[x]) dfs(x);
    }
}

void dia(int now, int lst, int dep) {
    if (dep > maxDep) maxDep = dep, maxDepID = now;
    for (auto x : adj[now]) {
        if (x != lst) dia(x, now, dep + 1);
    }
}

int32_t main() {
    fastIO();
    
    int n, l, u, v;
    cin >> n >> l;
    
    for (int i = 0; i < l; ++i) {
        cin >> u >> v, adj[u].eb(v), adj[v].eb(u);
    }
    
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            dfs(i);
            maxDep = -1; dia(i, -1, 0);
            maxDep = -1; dia(maxDepID, -1, 0);
            all_dep.eb((maxDep + 1) / 2);
            maxMaxDep = max(maxMaxDep, maxDep);
        }
    }
    sort(ALL(all_dep), [](auto a, auto b) {return a > b;});
    
    if (all_dep.size() == 1) {
        cout << maxMaxDep << "\n";
    }
    else if (all_dep.size() == 2) {
        cout << max(maxMaxDep, all_dep[0] + all_dep[1] + 1) << "\n";
    }
    else {
        cout << max({maxMaxDep,
                     all_dep[0] + all_dep[1] + 1,
                     all_dep[1] + all_dep[2] + 2}) << "\n";
    }
    
    return 0;
}