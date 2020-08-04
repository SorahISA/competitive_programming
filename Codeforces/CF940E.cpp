// #pragma GCC target("avx2")
#pragma GCC optimize("Ofast", "unroll-loops")

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

const int INF = 1LL << 60;
const int maxn = 1E5 + 5;

int32_t main() {
    fastIO();
    
    int n, c;
    cin >> n >> c;
    
    vector<int> v(n), sum(n);
    for (auto &x : v) cin >> x;
    partial_sum(ALL(v), sum.begin());
    
    int dp[n][2];
    dp[0][0] = v[0];
    dp[0][1] = c == 1 ? 0LL : INF;
    deque<pii> deq{{v[0], 0}};
    for (int i = 1; i < n; ++i) {
        while (!deq.empty() and deq.back().X >= v[i]) deq.pop_back();
        deq.push_back({v[i], i});
        if (deq.front().Y == i - c) deq.pop_front();
        
        dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + v[i];
        if (i < c - 1) dp[i][1] = INF;
        else if (i == c - 1) dp[i][1] = sum[i] - deq.front().X;
        else dp[i][1] = min(dp[i - c][0], dp[i - c][1]) + (sum[i] - sum[i - c]) - deq.front().X;
        // cout << dp[i][0] << " " << dp[i][1] << "\n";
    }
    
    cout << min(dp[n - 1][0], dp[n - 1][1]) << "\n";

    return 0;
}
