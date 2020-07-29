// #pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")
 
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
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;
 
#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
 
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(0, 1); \
                 auto rnd = bind(__dis, __gen);
 
const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 40000 + 5;

int n, k;
vector<int> adj[maxn], subSize(maxn, 0);
bitset<maxn> mods[maxn], tmp;

void dfs_init(int now, int lst) {
    subSize[now] = 1;
    for (auto x : adj[now]) {
        if (x == lst) continue;
        dfs_init(x, now);
        subSize[now] += subSize[x];
    }
}

void dfs(int now, int lst) {
    int lstX = 0;
    for (auto x : adj[now]) {
        if (x == lst) continue;
        if (subSize[x] == subSize[lstX]) {mods[x] = mods[lstX], dfs(x, now); continue;}
        lstX = x;
        mods[x] = mods[now] << 1;
        
        for (auto y : adj[now]) {
            if (y == lst or y == x) continue;
            tmp = mods[x]; tmp <<= subSize[y];
            mods[x] |= tmp;
        }
        
        dfs(x, now);
    }
}

int32_t main() {
    fastIO();
    
    int u, v;
    cin >> n >> k;
    
    for (int i = 0; i < n-1; ++i) cin >> u >> v, adj[u].eb(v), adj[v].eb(u);
    
    if (k == 1) {
        string _ans(n, 'Y');
        cout << _ans << "\n";
        return 0;
    }
    
    dfs_init(1, -1);
    for (int i = 1; i <= n; ++i) {
        sort(ALL(adj[i]), [](auto a, auto b) {
            return subSize[a] < subSize[b];
        });
    }
    mods[1][1] = 1, dfs(1, -1);
    
    char ans[n + 1], *res = "NY";
    ans[n] = '\0';
    for (int i = 1; i <= n; ++i) {
        for (int j = k; j <= n; j += k) mods[i][0] = mods[i][0] | mods[i][j];
        ans[i - 1] = res[mods[i][0]];
    }
    cout << ans << "\n";
    
    return 0;
}
