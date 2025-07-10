#include <bits/stdc++.h>
using namespace std;

void solve() {
    string S; cin >> S;
    int N = S.size();
    
    vector<vector<int>> pos(26);
    for (int i = 0; i < N; ++i) {
        pos[S[i] - 'a'].emplace_back(i+1);
    }
    
    vector<int> ans;
    int cost = abs(int(S[0]) - int(S[N-1]));
    int dir = (S[0] <= S[N-1] ? 1 : -1);
    for (int c = int(S[0] - 'a'); c != int(S[N-1] - 'a') + dir; c += dir) {
        copy(begin(pos[c]), end(pos[c]), back_inserter(ans));
    }
    
    cout << cost << " " << ans.size() << "\n";
    for (int x : ans) cout << x << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
