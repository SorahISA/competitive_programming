// #pragma GCC optimize("Ofast", "unroll-loops")
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

template<class T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << "\n";
        os << vec[i];
    }
    return os;
}

void solve() {
    int n, m; cin >> n >> m;
    
    vector<string> mp(n);
    for (auto &str : mp) cin >> str;
    
    for (int i = n-1; i >= 0; --i) {
        for (int j = m-1; j >= 0; --j) {
            
            if ((mp[i][j] == '#') or
                (i and mp[i-1][j] == '#') or
                (j and mp[i][j-1] == '#') or
                (i and j and mp[i-1][j-1] == '#')) {
                mp[i][j] = '#';
            }
            else {
                mp[i][j] = '.';
            }
        }
    }
    
    cout << mp << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}