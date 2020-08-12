#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
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
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

const int INF = 0x7fffffffffffffff;
const int maxn = 100 + 5;

vector<vector<int>> vec[maxn];
vector<int> dp(maxn, INF);

int32_t main() {
    fastIO();
    dp[0] = dp[1] = 1;
    
    int g, n, m, a, tmp;
    cin >> g >> n >> m;
    assert(m == 0);
    
    for (int i = 0; i < n; ++i) {
        cin >> a >> tmp;
        vector<int> v(tmp);
        for (auto &x : v) cin >> x;
        vec[a].eb(v);
    }
    
    for (int i = 0; i < maxn; ++i) {
        for (int j = 2; j < g; ++j) {
            for (auto v : vec[j]) {
                int val = 0, fl = 1;
                for (auto x : v) {
                    if (dp[x] == INF) {fl = 0; break;}
                    val += dp[x];
                }
                if (fl) dp[j] = min(dp[j], val);
            }
        }
    }
    
    for (int i = 2; i < g; ++i) {
        if (dp[i] == INF) cout << "YES\n";
        else cout << "NO " << dp[i] << "\n";
    }
    
    return 0;
}