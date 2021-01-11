// #pragma GCC target("avx2")
// #pragma GCC optimize("O3", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define RALL(x) (x).rbegin(), (x).rend()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

void solve() {
    int n, L; cin >> n >> L;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    
    int tok = -1;
    for (int i = 0; i < n-1; ++i) {
        if (v[i] + v[i+1] >= L) tok = i+1;
    }
    
    if (tok == -1) {
        cout << "Impossible\n";
    }
    else {
        cout << "Possible\n";
        for (int i = 1; i < tok; ++i) cout << i << "\n";
        for (int i = n-1; i > tok; --i) cout << i << "\n";
        cout << tok << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
