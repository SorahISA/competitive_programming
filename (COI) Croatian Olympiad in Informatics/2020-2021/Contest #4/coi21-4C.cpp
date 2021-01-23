// #pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

void solve() {
    int n; cin >> n;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    
    vector<int> dis(n, 0);
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (v[i] % v[j] == 0) dis[i] = max(dis[i], dis[j] + 1);
        }
    }
    
    for (int i = 1, tok = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (dis[i] / 4 == dis[j] / 4) cout << 1;
            else if (dis[i] / 16 == dis[j] / 16) cout << 2;
            else cout << 3;
            cout << " \n"[j == i-1];
        }
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
