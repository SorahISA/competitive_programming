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
#define RALL(x) (x).rbegin(), (x).rend()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

void solve() {
    int n, k; cin >> n >> k;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    sort(RALL(v));
    
    // for (auto x : v) cout << x << " "; cout << "\n";
    
    Prior<int> pq;
    for (int i = 0; i < k+1; ++i) pq.push(0);
    
    int ans = 0;
    for (auto x : v) {
        int tp = pq.top(); pq.pop();
        // cout << tp << "\n";
        ans += tp, pq.push(tp + x);
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
