#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;

#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

const int MAXN = 55;
int a[MAXN];
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i=0;i<n;++i) {
        int k;
        cin >> k;
        for (int j=0;j<k;++j) {
            int x;
            cin >> x;
            a[i] |= (1LL<<x);
        }
    }
    int p,q;
    cin >> p >> q;
    int mask = 0;
    for (int i=0;i<p;++i) {
        int x;
        cin >> x;
        mask |= (1LL<<x);
    }
    int ans = 0;
    for (int i=0;i<n;++i) {
        int cur = mask & a[i];
        if (__builtin_popcountll(cur) >= q) ans++;
    }
    cout << ans << '\n';
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
