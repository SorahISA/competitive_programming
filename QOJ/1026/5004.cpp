#include <bits/stdc++.h>
using namespace std;

void solve() {
    int C; cin >> C;
    
    vector<tuple<int, string, int, int, int, int, int>> team(6);
    for (auto &[sc, name, pt, pu, rt, ru, f] : team) {
        cin >> name >> pt >> pu >> rt >> ru >> f;
        sc = 56 * ru + 24 * rt + 14 * pu + 6 * pt + 3 * f;
    }
    sort(rbegin(team), rend(team));
    
    for (int i = 0; i < 6; ++i) {
        if (get<1>(team[i]) == "Taiwan") {
            cout << min(get<5>(team[i]), C / 6 + (C % 6 > i)) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; ++i) {
        solve();
    }
    
    return 0;
}
