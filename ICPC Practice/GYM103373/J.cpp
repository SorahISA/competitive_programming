#include <bits/stdc++.h>
using namespace std;

#define int long long

#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

void solve() {
    string S, T; cin >> S >> T;
    
    int flag = 1;
    for (auto &c : S) if (!isdigit(c)) flag = 0;
    for (auto &c : T) if (!isdigit(c)) flag = 0;
    
    if (flag) cout << stoi(S) - stoi(T) << "\n";
    else      cout << "NaN" << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}