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

void solve() {
    int n, ans = 0;
    string s; cin >> s, n = s.size();
    
    for (int i = 0; i < n; ++i) {
        if ((i >= 1 and s[i] == s[i-1]) or (i >= 2 and s[i] == s[i-2])) {
            ++ans, s[i] = '_';
        }
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}
