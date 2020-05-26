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
const int maxn = 1E4 + 5;
const int maxk = 100 + 5;

int save[maxn][maxk];
int dp[maxn][maxk];

int32_t main() {
    fastIO();
    
    int n, m, K;
    cin >> n >> m >> K;
    
    vector<int> wi(n), si(m);
    for (auto &x : wi) cin >> x;
    for (auto &x : si) cin >> x;
    
    /// save[i][j] : save tree[i] for j times ///
    
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = 0; j < m; ++j) {
            if (si[j] > wi[i]) ++cnt;
            if (cnt > K) break;
            ++save[i][cnt];
        }
        partial_sum(save[i], save[i] + maxk, save[i]);
    }
    
    /// dp[i][j] : saving tree[1..i] using j masks ///
    
    for (int i = 0; i <= K; ++i) dp[0][i] = save[0][i];
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= K; ++j) {
            for (int k = 0; k <= j; ++k) dp[i][j] = max(dp[i][j], dp[i-1][k] + save[i][j-k]);
        }
    }
    
    cout << dp[n-1][K] << "\n";
    
    return 0;
}
