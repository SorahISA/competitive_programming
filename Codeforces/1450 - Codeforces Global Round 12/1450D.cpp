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
    int n; cin >> n;
    string ans(n, '0');
    
    vector<int> v(n), app(n), seq, minV(n);
    for (auto &x : v) cin >> x, app[--x] = 1;
    if (accumulate(ALL(app), 0) == n) ans[0] = '1';
    if (app[0]) ans[n-1] = '1';
    
    for (int l = 0, r = n-1; l <= r; ) {
        if (v[l] < v[r]) seq.eb(v[l++]);
        else             seq.eb(v[r--]);
    }
    
    minV[n-1] = n;
    for (int i = n-2; i >= 0; --i) minV[i] = min(minV[i+1], seq[i+1]);
    
    // for (auto x : seq)  cout << x << " "; cout << "\n";
    // for (auto x : minV) cout << x << " "; cout << "\n";
    
    for (int i = 0; i < n-1; ++i) {
        if (seq[i] == i and minV[i] == i+1) ans[n-i-2] = '1';
        else break;
    }
    
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}
