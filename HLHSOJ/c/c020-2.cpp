// #pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

// #define int long long
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
                 uniform_int_distribution<int> __dis(2, 1E18); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 2E6 + 5;

int cnt = 0, lim, vis[maxn]; /// 0 for not visited, 1 for visited, 2 for in-queue
char ans[maxn];
vector<int> adj[maxn];

void dfs(int now) {
    stack<int> stk; stk.push(now);
    while (!stk.empty()) {
        int nxt = stk.top(); stk.pop();
        for (auto x : adj[nxt]) {
            if (x > lim) vis[x] = 2;
            else if (vis[x] != 1) ++cnt, vis[x] = 1, stk.push(x);
        }
    }
}

int32_t main() {
    // fastIO();
    
    int n, m, u, v;
    scanf("%d %d", &n, &m);
    while (m--) {
        scanf("%d %d", &u, &v);
        if (u ^ v) adj[u].eb(v), adj[v].eb(u);
    }
    
    vis[0] = 1;
    for (lim = 0; lim < n; ++lim) {
        if (vis[lim]) ++cnt, vis[lim] = 1, dfs(lim);
        ans[lim] = cnt-1 == lim ? '1' : '0';
    }
    ans[n] = '\0';
    puts(ans);
    
    return 0;
}
