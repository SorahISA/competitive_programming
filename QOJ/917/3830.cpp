#include <bits/stdc++.h>
using namespace std;

#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front

#define SZ(x) ((int)(x).size())
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)

#ifdef local
#define fastIO() void()
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#endif

void solve() {
    vector<deque<int>> bracket(1);
    
    string S;
    int line = 0, tmp_line;
    while (cin >> S and S != "END") {
        ++line, bracket.eb(0);
        if (S[0] == 'l') {
            cin >> S;
        }
        else {
            cin >> S, cin >> S, cin >> S;
            tmp_line = stoi(S.substr(5));
            bracket[line].eb(line);
            if (tmp_line > line) continue;
            bracket[tmp_line].ef(line);
        }
    }
    
    deque<int> stk;
    for (auto &vec : bracket) for (int &x : vec) {
        if (SZ(stk) and stk[0] == x) stk.pf();
        else stk.ef(x);
    }
    cout << (SZ(stk) == 0 ? "good" : "bad") << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}
