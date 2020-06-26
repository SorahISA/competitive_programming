#include <bits/stdc++.h>
using namespace std;

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

int main() {
    fastIO();
    
    int n, m, q, k, tmp, u, v;
    queue<int> bfs;
    cin >> n >> m >> q >> k;
    
    vector<int> adj[n], dis(n, -1);
    
    while (q--) {
        cin >> tmp, --tmp;
        dis[tmp] = 0;
        bfs.push(tmp);
    }
    
    for (int i = 0; i < m; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    while (!bfs.empty()) {
        int nxt = bfs.front(); bfs.pop();
        for (auto x : adj[nxt]) {
            if (dis[x] == -1) {
                dis[x] = dis[nxt] + 1;
                bfs.push(x);
            }
        }
    }
    
    int trans[n];
    trans[0] = 0;
    for (int i = 1, tok = 1; tok < n; ++i) {
        for (int j = 0; j < i*k and tok < n; ++j, ++tok) {
            trans[tok] = i;
        }
    }
    
    for (int i = 0; i < n; ++i) cout << trans[dis[i]] << " \n"[i == n-1];
    
    return 0;
}
