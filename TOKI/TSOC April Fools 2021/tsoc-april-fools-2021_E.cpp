#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

void solve() {
    int n, ret; cin >> n;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n-1; ++j) {
            cout << "E " << (i&1 ? -1 : 1) << "\n" << flush;
            cin >> ret; if (ret) return;
        }
        cout << "N 1\n" << flush;
        cin >> ret; if (ret) return;
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}