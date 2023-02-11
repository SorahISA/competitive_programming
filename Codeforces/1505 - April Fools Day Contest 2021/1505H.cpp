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

int a[] = {44, 12, 49, 17, 10, 25, 18, 17, 24, 25, 20};
int b[] = {55, 99, 61, 99, 91, 90, 98, 30, 25, 30, 29};

void solve() {
    for (int i = 0; i < 11; ++i) cout << (char)(a[i] + b[i]);
    cout << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}

/*
44, 12, 49, 17, 10, 25, 18, 17, 24, 25, 20
55, 99, 61, 99, 91, 90, 98, 30, 25, 30, 29
*/