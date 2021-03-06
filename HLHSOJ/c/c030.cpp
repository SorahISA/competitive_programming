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

const int INF = 3E18;
const int mod = 1E9 + 7;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<pii> v(n);
    for (auto &x : v) cin >> x.X, --x.X;
    for (auto &x : v) cin >> x.Y, --x.Y;
    sort(ALL(v));

    vector<int> ring;
    vector<bool> vis(n, 0);
    for (int i = 0; i < n; ++i) {
        if (vis[i]) continue;
        int now = i, cnt = 0;
        while (!vis[now]) {
            vis[now] = 1, ++cnt;
            now = v[now].Y;
        }
        ring.eb(cnt);
    }
    sort(ALL(ring));

    int ans = 0;
    for (auto x : ring) {
        if (k >= x-1) k -= x - 1, ans += x;
    }
    
    cout << min(ans + k, n) << "\n";
}

int32_t main() {
    fastIO();
    
    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}
