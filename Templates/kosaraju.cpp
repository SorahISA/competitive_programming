// #pragma GCC target("avx2")
#pragma GCC optimize("Ofast", "unroll-loops")

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
// template <typename T>
// using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using pii = pair<int, int>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int INF = 0x7f7f7f7f;
const int maxn = 1E4 + 5;

int tok_scc = 0;
vector<int> adj1[maxn], adj2[maxn], dfn(maxn, -1), vis1(maxn), scc(maxn);
vector<int> adj3[maxn], degI(maxn), vis2(maxn), val(maxn), val2(maxn), dp(maxn);
stack<int> id;

void dfs1(int now) {
    vis1[now] = 1;
    for (auto x : adj1[now]) {
        if (!vis1[x]) dfs1(x);
    }
    id.push(now);
}

void dfs2(int now) {
    scc[now] = tok_scc;
    for (auto x : adj2[now]) {
        if (!scc[x]) dfs2(x);
    }
}

void dfs3(int now) {
    for (auto x : adj3[now]) {
        dp[x] = max(dp[x], dp[now] + val2[x]);
        if (++vis2[x] == degI[x]) dfs3(x);
    }
}

void kosaraju(int n) {
    for (int i = 1; i <= n; ++i) {
        if (!vis1[i]) dfs1(i);
    }
    
    while (!id.empty()) {
        if (scc[id.top()]) {id.pop(); continue;}
        ++tok_scc, dfs2(id.top()), id.pop();
    }
}

int32_t main() {
    fastIO();
    
    int n, m, u, v;
    cin >> n >> m;
    
    for (int i = 1; i <= n; ++i) cin >> val[i];
    
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        adj1[u].eb(v), adj2[v].eb(u);
    }
    
    kosaraju(n);
    
    for (int i = 1; i <= n; ++i) {
        val2[scc[i]] += val[i];
        for (auto x : adj1[i]) {
            if (scc[i] != scc[x]) adj3[scc[i]].eb(scc[x]);
        }
    }
    
    for (int i = 1; i <= tok_scc; ++i) {
        sort(ALL(adj3[i]));
        adj3[i].resize(unique(ALL(adj3[i])) - adj3[i].begin());
        for (auto x : adj3[i]) ++degI[x];
    }
    
    for (int i = 1; i <= tok_scc; ++i) {
        if (degI[i] == 0) dp[i] = val2[i], dfs3(i);
    }
    
    // for (int i = 1; i <= n; ++i) cout << scc[i] << " \n"[i == n];
    
    cout << *max_element(ALL(dp)) << "\n";
    
    return 0;
}
