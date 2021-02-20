#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

void solve() {
    int h, w; cin >> h >> w;
    
    vector<string> mp(h);
    for (auto &str : mp) cin >> str;
    
    for (int i = 0; i < h-1; ++i) {
        for (int j = 0; j < w; ++j) {
            cout << ".#"[mp[i][j] == '#' or i == 0 or (j & 1)];
        }
        cout << "\n";
    }
    cout << string(w, '.') << "\n";
    cout << "\n";
    
    cout << string(w, '.') << "\n";
    for (int i = 1; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cout << ".#"[mp[i][j] == '#' or i == h-1 or (~j & 1)];
        }
        cout << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}