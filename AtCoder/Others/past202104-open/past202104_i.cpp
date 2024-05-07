#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define ef push_front
#define pf pop_front
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template <typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int MAXN = 1e2+5;
int dp[MAXN][MAXN][MAXN*2], d[MAXN][MAXN];
void solve() {
    int n,m;
    cin >> n >> m;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=m;++j) {
            cin >> d[i][j];
        }
    }
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=m;++j) {
            for (int k=1;k<=i+j-1;++k) {
                chmax(dp[i][j][k], max(dp[i][j-1][k], dp[i-1][j][k]));
                chmax(dp[i][j][k], max(dp[i][j-1][k-1], dp[i-1][j][k-1]) + d[i][j]);
            }
        }
    }
    for (int i=1;i<=n+m-1;++i) {
        cout << dp[n][m][i] << '\n';
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
