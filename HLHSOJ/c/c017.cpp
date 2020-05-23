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
const int maxn = 1 << 22;

bitset<maxn> ans;
int adj[25][25];

int32_t main() {
    fastIO();
    
    int n, m, u, v, maxAns = 1;
    cin >> n >> m;
    while (m--) cin >> u >> v, --u, --v, adj[u][v] = adj[v][u] = 1;
    
    for (int i = 1; i < (1<<n); ++i) {
        if (__builtin_popcount(i) == 1) {ans[i] = 1; continue;}
        
        for (int j = 0; j < n; ++j) {
            if ((i & (1 << j)) and ans[i^(1<<j)]) {
                int fl = 1;
                for (int k = 0; k < n; ++k) {
                    if (((i ^ (1 << j)) & (1 << k)) and !adj[j][k]) {fl = 0; break;}
                }
                if (fl) ans[i] = 1;
            }
        }
        
        if (ans[i]) maxAns = max(maxAns, (int)__builtin_popcount(i));
    }
    
    cout << maxAns << "\n";
    
    return 0;
}
