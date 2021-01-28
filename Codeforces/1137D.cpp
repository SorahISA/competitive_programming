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

int next(vector<int> v) {
    cout << "next ";
    for (auto x : v) cout << x << " ";
    cout << "\n" << flush;
    
    int sz, tok = 0; cin >> sz;
    string tmp; while (tok++ < sz and cin >> tmp);
    return sz;
}

void solve() {
    while (next({0, 1}) and next({1}) != 2);
    while (next({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) != 1);
    cout << "done\n" << flush;
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
