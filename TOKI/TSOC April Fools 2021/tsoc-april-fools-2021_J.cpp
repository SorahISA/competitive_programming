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
    string w1, w2, b1, b2; cin >> w1 >> w2 >> b1 >> b2;
    int sw = ((w1[0] - 'a') ^ (w1[1] - '1') ^ (w2[0] - 'a') ^ (w2[1] - '1')) & 1;
    int sb = ((b1[0] - 'a') ^ (b1[1] - '1') ^ (b2[0] - 'a') ^ (b2[1] - '1')) & 1;
    if (sw == sb) cout << "White\n";
    else cout << "Black\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}