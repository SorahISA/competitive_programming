#include <bits/stdc++.h>
using namespace std;

#define int long long

#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

void solve() {
    int N; cin >> N;
    
    vector<tuple<int, int, int, string>> vec(N);
    for (auto &[g, s, b, name] : vec) {
        cin >> g >> s >> b;
        cin.ignore(), getline(cin, name);
    }
    sort(RALL(vec));
    
    cout << get<3>(vec[0]) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}