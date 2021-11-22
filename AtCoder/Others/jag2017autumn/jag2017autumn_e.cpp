#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T> using Prior = std::priority_queue<T>;
template<typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &x, T y) {return x > y ? x = y, 1 : 0;}
template<typename T> bool chmax(T &x, T y) {/* cout << " -> " << y << "\n"; */ return x < y ? x = y, 1 : 0;}

const int maxn = 1E5 + 5;

int N, K;
vector<int> adj[maxn], cnt(maxn, 0);

int dfs(int now, int lst) {
    int sz = 1;
    for (auto x : adj[now]) {
        if (x != lst) {
            int ch_sz = dfs(x, now);
            if (ch_sz >= K) ++cnt[now];
            sz += ch_sz;
        }
    }
    if (N - sz >= K) ++cnt[now];
    return sz;
}

int dfs_calc(int now, int lst, int &ans) {
    vector<int> ch_ans;
    for (auto x : adj[now]) {
        if (x != lst) ch_ans.eb(dfs_calc(x, now, ans));
    }
    // cout << now << "\n";
    if (SZ(ch_ans)) {
        sort(RALL(ch_ans));
        chmax(ans, ch_ans[0] + cnt[now]);
        if (SZ(ch_ans) >= 2) chmax(ans, ch_ans[0] + ch_ans[1] + cnt[now]);
        return max(ch_ans[0], (int)0) + cnt[now];
    }
    return cnt[now];
}

void solve() {
    cin >> N >> K;
    
    for (int i = 0; i < N-1; ++i) {
        int u, v; cin >> u >> v, adj[u].eb(v), adj[v].eb(u);
    }
    
    dfs(1, -1);
    
    /// find a path with maximum sum - 2*(sz-1) ///
    
    for (int i = 1; i <= N; ++i) cnt[i] -= 2;
    
    /// find a path with maximum sum + 2 ///
    
    int ans = -2;
    dfs_calc(1, -1, ans);
    ans += 2;
    
    for (int i = 1; i <= N; ++i) {
        if (SZ(adj[i]) > cnt[i] + 2) chmax(ans, cnt[i] + 2);
    }
    
    cout << ans << "\n";
}

int32_t main() {
    // fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}