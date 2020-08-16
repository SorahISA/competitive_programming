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
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E18;
const int mod = 1E9 + 7;

void solve() {
    int n;
    cin >> n;
    
    vector<int> v1(n), v2(n), cnt(n + 1);
    for (auto &x : v1) cin >> x;
    for (auto &x : v2) cin >> x;
    
    vector<pii> adj[n + 1];
    for (int i = 0; i < n; ++i) {
        if (++cnt[v1[i]] > 2 or ++cnt[v2[i]] > 2) {
            cout << -1 << "\n";
            return;
        }
        adj[v1[i]].eb(v2[i], i + 1), adj[v2[i]].eb(-v1[i], i + 1);
    }
    
    vector<int> vis(n + 1), ans;
    for (int i = 1; i <= n; ++i) {
        int now = i, lst = -1;
        vector<int> pos, neg;
        while (!vis[now]) {
            vis[now] = 1;
            if (abs(adj[now][0].X) != lst) {
                if (adj[now][0].X > 0) pos.eb(adj[now][0].Y);
                else                   neg.eb(adj[now][0].Y);
                lst = now, now = abs(adj[now][0].X);
            }
            else {
                if (adj[now][1].X > 0) pos.eb(adj[now][1].Y);
                else                   neg.eb(adj[now][1].Y);
                lst = now, now = abs(adj[now][1].X);
            }
        }
        
        if (pos.size() <= neg.size()) {
            for (auto x : pos) ans.eb(x);
        }
        else {
            for (auto x : neg) ans.eb(x);
        }
    }
    
    cout << ans.size() << "\n";
    for (auto x : ans) cout << x << " ";
    cout << "\n";
}

int32_t main() {
    fastIO();
    
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
