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

int a[26] = {
    10010, 11020, 20011, 21012, 11011,
    21021, 22022, 12021, 11011, 12012,
    10120, 11130, 20121, 21122, 11121,
    21131, 22132, 12131, 11121, 12122,
    10221, 11231, 12113, 20222, 21223, 11222,
};

void solve() {
    int num = 0, tmp;
    cin >> tmp, num += 10000 * tmp;
    cin >> tmp, num += 1000 * tmp;
    cin >> tmp, num += 100 * tmp;
    cin >> tmp, num += 10 * tmp;
    cin >> tmp, num += 1 * tmp;
    for (int i = 0; i < 26; ++i) {
        if (num == a[i]) return cout << (char)('a'+i), void();
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    cout << "\n";
    
    return 0;
}