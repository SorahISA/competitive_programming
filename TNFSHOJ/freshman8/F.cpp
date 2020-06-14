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

int32_t main() {
    fastIO();
    
    int n, m, k, max1 = 0, max2 = 0;
    cin >> n >> m >> k;
    
    vector<pii> cp(n);
    for (auto &[c, p] : cp) cin >> c >> p, p /= c;
    sort(ALL(cp), [](auto a, auto b) {
        if (a.Y == b.Y) return a.X < b.X;
        return a.Y > b.Y;
    });
    
    // for (auto [c, p] : cp) cout << c << " " << p << "\n";
    
    int cnt1 = m - k;
    for (int i = 0; i < n; ++i) {
        if (cnt1 >= cp[i].X) cnt1 -= cp[i].X, max1 += cp[i].X * cp[i].Y;
        else {max1 += cnt1 * cp[i].Y; break;}
    }
    
    int dp[m + 5];
    memset(dp, 0x00, sizeof(dp));
    
    for (int i = 0; i < n; ++i) {
        for (int j = m; j >= cp[i].X; --j) {
            dp[j] = max(dp[j], dp[j - cp[i].X] + cp[i].X * cp[i].Y);
        }
    }
    max2 = dp[m];
    
    cout << max(max1, max2) << "\n";
    
    return 0;
}
