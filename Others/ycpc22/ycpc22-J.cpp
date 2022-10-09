#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define eb emplace_back
#define X first
#define Y second
#ifdef local
#define debug(...) do{\
    fprintf(stderr, "LINE %d: (%s) = ", __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template <typename T> void _do(T &&_x) {cerr << _x << endl;}
template <typename T, typename ...S> void _do(T &&_x, S &&..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs){return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs){return lhs < rhs ? lhs = rhs, 1 : 0;}

const int MAXN = 2e5+5;
vector<int> tp, a;
vector<int> e[MAXN], re[MAXN];
set<int> G[MAXN];
int scc[MAXN], dp[MAXN], sum[MAXN];
bitset<MAXN> vis;
void dfs1(int x) {
    vis[x] = 1;
    for (auto i : e[x]) {
        if (vis[i]) continue;
        dfs1(i);
    }
    tp.eb(x);
}
void dfs2(int x, int cnt) {
    vis[x] = 1, scc[x] = cnt;
    for (auto i : re[x]) {
        if (vis[i]) continue;
        dfs2(i, cnt);
    }
}
int cal(int x) {
    if(vis[x]) return dp[x];
    vis[x] = 1;
    dp[x] = 0;
    for(int y : G[x]) {
        dp[x] = max(dp[x], cal(y));
    }
    dp[x] += sum[x];
    return dp[x];
}
void solve() {
    int n,m;
    cin >> n >> m;
    for (int i=0;i<n;++i) {
        int x;
        cin >> x;
        a.eb(x);
    }
    for (int i=0;i<m;++i) {
        int u,v;
        cin >> u >> v;
        e[u].eb(v);
        re[v].eb(u);
    }
    for (int i=0;i<n;++i) if (!vis[i]) dfs1(i);
    vis.reset();
    int cnt = 0;
    for (int i=n-1;i>=0;--i) if (!vis[tp[i]]) dfs2(tp[i], cnt++);
    for(int i=0;i<n;i++) {
        sum[scc[i]] += a[i];
        debug(scc[i]);
        for(auto j:e[i]) {
            if(scc[i] != scc[j]) {
                G[scc[i]].insert(scc[j]);
            }
        }
    }
    int ans = 0;
    vis.reset();
    for(int i = 0; i < cnt; i++) {
        debug(cal(i));
        debug(sum[i]);
        ans = max(ans, cal(i));
    }
    cout << ans << '\n';
}

signed main() {
    IOS();
    int _ = 1;
    // cin >> _;
    for (int i=1;i<=_;++i) {
        solve();
    }
}
