#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;

#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

const int MAXN = 5e5+5;
int a[MAXN];
void solve() {
    int n,k;
    cin >> n >> k;
    for (int i=0;i<n;++i) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i=0;i<k;++i) {
        ans += a[i];
    }
    cout << ans << '\n';
    for (int i=k;i<n;++i) {
        ans -= a[i-k];
        ans += a[i];
        cout << ans << '\n';
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
