// #pragma GCC optimize("Ofast", "unroll-loops")
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
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxn = 2000 + 5;
const int mod = 1E9 + 7;

map<string, int> cnt;
int cnm[maxn][maxn];

void init() {
    for (int i = 0; i < maxn; ++i) cnm[i][0] = cnm[i][i] = 1;
    for (int i = 2; i < maxn; ++i) {
        for (int j = 1; j < i; ++j) cnm[i][j] = (cnm[i-1][j-1] + cnm[i-1][j]) % mod;
    }
}

void solve() {
    int n, k; cin >> n >> k;
    
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        sort(ALL(s)), ++cnt[s];
    }
    
    vector<int> nums;
    for (auto [str, app] : cnt) nums.eb(app);
    sort(ALL(nums)); /// useless
    
    // cout << nums << "\n";
    
    int dp[nums.size()+1][k+1];
    memset(dp, 0x00, sizeof(dp)); dp[0][0] = 1;
    /// dp[i][j]: use i stacks to form j pairs ///
    for (int i = 1; i <= nums.size(); ++i) {
        for (int l = 0; l <= nums[i-1]; ++l) {
            for (int j = cnm[l][2]; j <= k; ++j) {
                dp[i][j] = (dp[i][j] + dp[i-1][j-cnm[l][2]] * cnm[nums[i-1]][l]) % mod;
            }
        }
    }
    cout << dp[nums.size()][k] << "\n";
    
    // for (int i = 0; i <= nums.size(); ++i) {
        // for (int j = 0; j <= k; ++j) cout << dp[i][j] << " \n"[j == k];
    // }
}

int32_t main() {
    fastIO();
    init();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}