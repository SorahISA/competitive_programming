#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;

#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

const int maxc = 1E5 + 10;

void solve() {
    int N, C; cin >> N >> C;
    
    double sum = 0.0;
    vector<pii> vec(N);
    for (auto &[x, y] : vec) cin >> x >> y, sum += (C - y) * (C - y);
    sort(ALL(vec));
    
    auto calc = [&](double p) {
        double cost = 0.0;
        for (auto &[x, y] : vec) cost += (x - p) * (x - p);
        return cost;
    };
    
    double lo = -maxc, hi = maxc, milo, mihi;
    for (int t = 1; t <= 100; ++t) {
        milo = (lo + lo + hi)     / 3;
        mihi = (lo + hi + hi) / 3;
        if (calc(milo) < calc(mihi)) hi = mihi;
        else                         lo = milo;
    }
    cout << fixed << setprecision(20) << sum + calc(lo) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
