#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N, K; cin >> N >> K;
    string S; cin >> S;
    
    vector<pair<int, int>> cnt(26);
    for (char c : S) {
        if (islower(c)) ++cnt[c-'a'].first;
        else            ++cnt[c-'A'].second;
    }
    
    int ans = 0;
    for (auto [lo, up] : cnt) {
        ans += min(lo, up) + min(abs(lo - up) / 2, K);
        K -= min(abs(lo - up) / 2, K);
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
