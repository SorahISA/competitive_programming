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
                 uniform_int_distribution<int> __dis(1, 7); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 2E5 + 5;

int32_t main() {
    fastIO();
    
    int R, G, B;
    cin >> R >> G >> B;
    
    vector<int> r(R), g(G), b(B);
    for (auto &x : r) cin >> x; sort(ALL(r), [](auto v1, auto v2) {return v1 > v2;});
    for (auto &x : g) cin >> x; sort(ALL(g), [](auto v1, auto v2) {return v1 > v2;});
    for (auto &x : b) cin >> x; sort(ALL(b), [](auto v1, auto v2) {return v1 > v2;});
    r.eb(0), g.eb(0), b.eb(0);
    
    int dp[R + 5][G + 5][B + 5];
    memset(dp, 0x00, sizeof(dp));
    
    for (int i = 0; i <= R; ++i) {
        for (int j = 0; j <= G; ++j) {
            for (int k = 0; k <= B; ++k) {
                dp[i+1][j+1][k] = max(dp[i+1][j+1][k], dp[i][j][k] + r[i] * g[j]);
                dp[i+1][j][k+1] = max(dp[i+1][j][k+1], dp[i][j][k] + r[i] * b[k]);
                dp[i][j+1][k+1] = max(dp[i][j+1][k+1], dp[i][j][k] + g[j] * b[k]);
            }
        }
    }
    
    int ans = 0;
    for (int i = 0; i <= R; ++i) {
        for (int j = 0; j <= G; ++j) {
            for (int k = 0; k <= B; ++k) {
                // cout << i << " " << j << " " << k << " " << dp[i][j][k] << "\n";
                if (~(i + j + k) & 1) ans = max(ans, dp[i][j][k]);
            }
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
