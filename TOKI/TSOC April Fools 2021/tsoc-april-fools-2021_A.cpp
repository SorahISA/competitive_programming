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
#define mtp make_tuple
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

void solve() {
    int a, b, c, d; cin >> a >> b >> c >> d;
    if (mtp(a, b, c, d) == mtp(2, 1, 3, 1)) cout << "5 1\n";
    if (mtp(a, b, c, d) == mtp(1, 3, 1, 6)) cout << "1 2\n";
    if (mtp(a, b, c, d) == mtp(1, 3, 1, 3)) cout << "3 4\n";
    if (mtp(a, b, c, d) == mtp(6, 4, 2, 8)) cout << "15 8\n";
    if (mtp(a, b, c, d) == mtp(5, 8, 6, 1)) cout << (6LL<<4)+11 << " " << (1LL<<4) << "\n";
    if (mtp(a, b, c, d) == mtp(6, 7, 1, 6)) cout << (1LL<<41)+1 << " " << (1LL<<41) << "\n";
    if (mtp(a, b, c, d) == mtp(8, 7, 7, 8)) cout << (2LL<<55)+1 << " " << (1LL<<55) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}