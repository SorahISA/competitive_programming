#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

void solve() {
    int n; cin >> n;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    
    vector<int> seg;
    int len = 1;
    for (int i = 1; i < n; ++i) {
        if (v[i] == v[i-1]) seg.eb(len), len = 1;
        else ++len;
    }
    seg.eb(len);
    
    if (seg.size() <= 3) cout << n << "\n";
    else {
        int ans = 0;
        for (int i = 2; i < seg.size(); ++i) ans = max(ans, seg[i-2] + seg[i-1] + seg[i]);
        cout << ans << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}