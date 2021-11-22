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
#define pb push_back
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

void solve() {
    int n; cin >> n;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    
    if (v.front() > 1 or v.back() > 1) return cout << "NO\n", void();
    for (auto x : v) if (x > 2) return cout << "NO\n", void();
    
    int sum = 0, cnt = 0;
    for (auto x : v) {
        cnt += !!x, sum += x;
        if (~sum & 1 and x == 2) return cout << "NO\n", void();
    }
    if (cnt == 1 or sum % 2) cout << "NO\n";
    else cout << "YES\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}