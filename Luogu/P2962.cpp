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

int32_t main() {
    fastIO();
    
    int n, m, u, v, mid;
    cin >> n >> m, mid = n / 2;
    
    vector<int> adj(n, 0);
    for (int i = 0; i < m; ++i) {
        cin >> u >> v, --u, --v;
        adj[u] ^= 1LL << v;
        adj[v] ^= 1LL << u;
    }
    for (int i = 0; i < n; ++i) adj[i] ^= 1LL << i;
    
    int stL[1 << mid], stR[1 << n-mid];
    memset(stL, 0x00, sizeof(stL));
    memset(stR, 0x00, sizeof(stR));
    for (int i = 1; i < (1<<mid); ++i) {
        int lb = i & -i, pl = __lg(lb);
        stL[i] = stL[i^lb] ^ adj[pl];
    }
    
    for (int i = 1<<mid; i < (1LL<<n); i += 1<<mid) {
        int lb = i & -i, pl = __lg(lb);
        stR[i >> mid] = stR[(i^lb) >> mid] ^ adj[pl];
    }
    
    map<int, int> allLeft;
    int ans = n;
    int full = (1LL << n) - 1;
    for (int i = 0; i < (1<<mid); ++i) {
        if (stL[i] == full) ans = min(ans, (int)__builtin_popcount(i));
        else if (allLeft[stL[i]]) allLeft[stL[i]] = min(allLeft[stL[i]], (int)__builtin_popcount(i));
        else allLeft[stL[i]] = __builtin_popcount(i);
    }
    
    for (int i = 0; i < (1<<n-mid); ++i) {
        if (stR[i] == full) ans = min(ans, (int)__builtin_popcount(i));
        else if (allLeft[full^stR[i]]) ans = min(ans, allLeft[full^stR[i]] + __builtin_popcount(i));
        // cout << (full ^ stR[i]) << " " << allLeft[full^stR[i]] << "\n";
    }
    
    cout << ans << "\n";
    
    return 0;
}
