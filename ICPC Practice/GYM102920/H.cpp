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
#define pb push_back
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

const int maxc = 60001;

bitset<maxc> up, dn, tmp;

void solve() {
    int n1, n2, n3, val;
    vector<int> mid;
    
    cin >> n1;
    while (n1--) cin >> val, up[val+30000] = 1;
    cin >> n2;
    for (int i = 0; i < n2; ++i) cin >> val, mid.eb(val);
    cin >> n3;
    while (n3--) cin >> val, dn[30000-val] = 1;
    
    int ans = 0;
    for (auto x : mid) {
        if (x < 0) tmp = (up << -x) & (dn >> -x);
        if (x > 0) tmp = (up >>  x) & (dn <<  x);
        if (x == 0) tmp = up & dn;
        ans += tmp.count();
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}