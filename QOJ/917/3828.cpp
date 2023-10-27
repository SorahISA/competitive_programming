#include <bits/stdc++.h>
using namespace std;

#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

void solve() {
    int m1; cin >> m1;
    for (int i = 0, u, v; i < m1; ++i) cin >> u >> v;
    int m2; cin >> m2;
    for (int i = 0, u, v; i < m2; ++i) cin >> u >> v;
    
    cout << (m1 == m2 ? "yes" : "no") << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}
