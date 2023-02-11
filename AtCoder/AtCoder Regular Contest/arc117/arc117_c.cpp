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

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int cnm[3][3] = {
    {1, 0, 0},
    {1, 1, 0},
    {1, 2, 1},
};

inline int lucas(int n, int m) {
    int ans = 1;
    while (n or m) {
        int ni = n % 3, mi = m % 3;
        ans = ans * cnm[ni][mi] % 3;
        n /= 3, m /= 3;
    }
    return ans;
}

void solve() {
    int n; string s; cin >> n >> s;
    
    // for (int i = 0; i < n; ++i) cout << lucas(n-1, i) << " \n"[i == n-1];
    
    map<char, int> cal{{'W', 0}, {'R', 1}, {'B', 2}};
    
    int score = 0;
    for (int i = 0; i < n; ++i) score += lucas(n-1, i) * cal[s[i]];
    if (n & 1) score *= -1;
    // cout << score << "\n";
    score = (3 - score % 3) % 3;
    // cout << score << "\n";
    
    cout << "WRB"[score] << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}