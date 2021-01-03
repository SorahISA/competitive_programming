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
    
    vector<int> val(n);
    for (auto &x : val) cin >> x;
    
    for (int i = 1; i < n; ++i) {
        if (val[i] <= val[i-1]) ++val[i];
    }
    // for (auto x : val) cout << x << " "; cout << "\n";
    val.resize(unique(ALL(val)) - val.begin());
    
    cout << val.size() << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}
