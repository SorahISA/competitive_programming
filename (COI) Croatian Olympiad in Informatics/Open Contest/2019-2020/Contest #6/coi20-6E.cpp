#include <bits/stdc++.h>
using namespace std;

#define int long long

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

const int mod = 1E9 + 7;

int _hash(string s) {
    int p = 257, mod = 13302843816923LL;
    int ans = 0;
    for (auto c : s) ans = (ans * p + c) % mod;
    return ans;
}

int32_t main() {
    int n, k;
    cin >> n >> k;
    
    string all[n][k];
    int hashes[n][k][3]; /// prefix, suffix, all
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            cin >> all[i][j];
            hashes[i][j][2] = _hash(all[i][j]);
            if (!i) continue;
            hashes[i][j][0] = _hash(all[i][j].substr(0, i));
            hashes[i][j][1] = _hash(all[i][j].substr(1));
        }
    }
    
    int dp[n][k];
    for (int i = 0; i < n; ++i) memset(dp[i], 0x00, sizeof(dp[i]));
    
    for (int j = 0; j < k; ++j) dp[0][j] = 1;
    
    for (int i = 1; i < n; ++i) {
        for (int j2 = 0; j2 < k; ++j2) {
            for (int j1 = 0; j1 < k; ++j1) {
                if (hashes[i][j2][0] == hashes[i-1][j1][2] or hashes[i][j2][1] == hashes[i-1][j1][2]) {
                    dp[i][j2] += dp[i-1][j1];
                }
            }
            dp[i][j2] %= mod;
        }
    }
    
    int ans = 0;
    for (int j = 0; j < k; ++j) ans += dp[n-1][j];
    
    cout << ans % mod << "\n";
    
    return 0;
}
