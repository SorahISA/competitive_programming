#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<class T>
inline ostream& operator << (ostream& os, vector<T> vec) {
    for (auto x : vec) os << x << " ";
    return os;
}

const int maxn = 5000 + 5;
const int INF = INT_MAX;

int dp[maxn][maxn], BIT[maxn];
vector<int> rightV[maxn];

void Add(int idx, int val) {
    while (idx < maxn) BIT[idx] += val, idx += idx & -idx;
}

int Sum(int idx, int ans = 0) {
    while (idx) ans += BIT[idx], idx -= idx & -idx;
    return ans;
}

void solve() {
    int n; cin >> n;
    
    vector<int> v(n), pl(n+1), pre_pl(n+1);
    for (auto &x : v) cin >> x;
    
    for (int i = 0; i < n; ++i) {
        rightV[v[i]].eb(0), rightV[v[i]].eb(n+1);
        for (int j = i+1; j < n; ++j) rightV[v[i]].eb(v[j]);
        sort(ALL(rightV[v[i]]));
    }
    for (int i = 0; i < n; ++i) pl[v[i]] = i + 1;
    partial_sum(ALL(pl), begin(pre_pl));
    
    // cout << pl << "\n" << pre_pl << "\n";
    // for (int i = 1; i <= n; ++i) cout << rightV[i] << "\n";
    
    for (int i = 1; i <= n; ++i) {
        memset(BIT, 0x00, sizeof(BIT));
        for (int k = i; k > 0; --k) Add(pl[k], 1), dp[i][0] -= Sum(pl[k]);
        
        for (int j = 1; j < i; ++j) {
            // cout << "dp[" << i << "][" << j << "]: ";
            dp[i][j] = dp[i][j-1] + Sum(pl[j]);
            
            int lo = 0, hi = rightV[j].size()-1, mi;
            while (lo < hi) {
                mi = lo + hi >> 1;
                if (rightV[j][mi] > i) hi = mi;
                else lo = mi + 1;
            }
            dp[i][j] -= lo;
            // cout << lo << " ";
            
            lo = 0, hi = rightV[j].size()-1;
            while (lo < hi) {
                mi = lo + hi >> 1;
                if (rightV[j][mi] > j) hi = mi;
                else lo = mi + 1;
            }
            dp[i][j] += lo;
            // cout << lo << "\n";
        }
    }
    
    // for (int i = 1; i <= n; ++i) {
        // cout << setw(2) << i << ": ";
        // for (int j = 0; j < n; ++j) cout << setw(3) << dp[i][j] << " \n"[j == n-1];
    // }
    
    int ans = INF;
    for (int j = 0; j < n; ++j) {
        for (int i = j+1; i <= n; ++i) dp[i][j] += pre_pl[i] - pre_pl[j];
        dp[j][j] = *min_element(dp[j], dp[j] + j);
        for (int i = j+1; i <= n; ++i) dp[i][j] += dp[j][j];
        ans = min(ans, dp[n][j]);
    }
    cout << ans << "\n";
    
    // for (int i = 1; i <= n; ++i) {
        // cout << setw(2) << i << ": ";
        // for (int j = 0; j < n; ++j) cout << setw(3) << dp[i][j] << " \n"[j == n-1];
    // }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}

/*
9
6 1 3 4 9 5 7 8 2
*/

/*
array after sort: [a_1, 1], [a_2, a_1), ..., [a_k, a_{k-1}), [N, a_k)
which 1 <= a_1 < a_2 < ... < a_k < N
dp[i][j]: the minimum operations to sort range (j, i] if [1, j] is sorted
*/