#include <bits/stdc++.h>
using namespace std;

#define int int64_t

void solve() {
    int N; cin >> N;
    
    vector<array<int, 3>> line(N);
    for (int i = 0, indent = 0; i < N; ++i) {
        string str; cin >> str;
        int s = count(begin(str), end(str), 's');
        int t = count(begin(str), end(str), 't');
        if (str.back() == '}') --indent;
        line[i] = {s, t, indent};
        // cerr << "debug: " << s << " " << t << " " << indent << "\n";
        if (str.back() == '{') ++indent;
    }
    
    for (int tab = 1; tab <= 1000; ++tab) {
        int indent = 0, flag = 1;
        for (auto [s, t, ind] : line) {
            if (indent == 0 and ind > 0) indent = (s + t * tab) / ind;
            if (s + t * tab != ind * indent) {flag = 0; break;}
        }
        if (flag) return cout << tab << "\n", void();
    }
    cout << -1 << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    solve();
    
    return 0;
}
