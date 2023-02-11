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

void solve() {
    int n, m; cin >> n >> m;
    
    vector<string> s(n);
    for (auto &str : s) cin >> str;
    
    int x = 0, y = 0, ans = s[0][0] == '*';
    for (int i = 0; i < n+m; ++i) {
             if (x == n-1) ans += s[x][++y] == '*';
        else if (y == m-1) ans += s[++x][y] == '*';
        else if (s[x+1][y] == '*') ans += s[++x][y] == '*';
        else                       ans += s[x][++y] == '*';
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}