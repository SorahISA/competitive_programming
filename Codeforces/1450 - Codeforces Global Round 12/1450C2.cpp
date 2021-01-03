#pragma GCC optimize("Ofast", "unroll-loops")

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

const int INF = 1E5;

void solve() {
    int n; cin >> n;
    
    vector<string> mp(n);
    for (auto &str : mp) cin >> str;
    
    int tok = 0;
    for (auto str : mp) for (auto c : str) tok += c != '.';
    
    vector<pii> cnt(3);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cnt[(i+j)%3].X += mp[i][j] == 'X';
            cnt[(i+j)%3].Y += mp[i][j] == 'O';
        }
    }
    
    int fl = 0;
    for (int p1 : {0, 1, 2}) for (int p2 : {0, 1, 2}) {
        if (p1 == p2 or fl) continue;
        if (cnt[p1].X + cnt[p2].Y <= tok / 3) {
            // cout << cnt[p1].X + cnt[p2].Y << "\n";
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if ((i + j) % 3 == p1 and mp[i][j] == 'X') mp[i][j] = 'O';
                    if ((i + j) % 3 == p2 and mp[i][j] == 'O') mp[i][j] = 'X';
                }
            }
            fl = 1;
        }
    }
    
    for (auto str : mp) cout << str << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}
