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
    int n, m; cin >> n >> m;
    vector<int> cnt(n, 1), poss(n, 0);
    poss[0] = 1;
    
    while (m--) {
        int x, y; cin >> x >> y, --x, --y;
        ++cnt[y], --cnt[x];
        poss[y] |= poss[x], poss[x] &= cnt[x] != 0;
    }
    cout << accumulate(ALL(poss), 0) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
