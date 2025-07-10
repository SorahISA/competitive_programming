#include <bits/stdc++.h>
using namespace std;

void solve() {
    string S, T; cin >> S >> T;
    
    auto size_to_int = [](string &str) -> int {
        if (str == "M") return 0;
        return int(str.size()) * (str.back() == 'S' ? -1 : 1);
    };
    
    if (S == T) cout << "=" << "\n";
    else cout << (size_to_int(S) < size_to_int(T) ? "<" : ">") << "\n";
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
