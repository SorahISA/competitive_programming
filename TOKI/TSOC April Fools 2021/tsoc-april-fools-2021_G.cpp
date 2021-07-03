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

string Reverse(int x) {
    string s;
    s.push_back(x%10 + '0'), s.push_back(x/10 + '0');
    return s;
}

void solve() {
    // cout << "0\n";
    // cout << "2331\n";
    // cout << "33312331\n";
    // cout << "533133312331\n";
    // cout << "8331533133312331\n";
    // cout << "24318331533133312331\n";
    int h = 13, m = 53;
    string s;
    for (int i = 20; i > 0; --i) {
        m -= i;
        if (m < 0) --h, m += 60;
        s += Reverse(m) + Reverse(h);
    }
    cout << s << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}