#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N; cin >> N;
    char c; cin >> c;
    string S; cin >> S;
    
    if (c == 'g') { cout << 0 << "\n"; return; }
    
    int ans = 0, green_pos = find(begin(S), end(S), 'g') - begin(S);
    for (int i = 0, cnt = 0, pos = green_pos; i < N; ++i, --pos) {
        if (pos < 0) pos += N;
        if (S[pos] == 'g') cnt = 0;
        else ++cnt;
        if (S[pos] == c) ans = max(ans, cnt);
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
