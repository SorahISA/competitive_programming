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

template<class T1, class T2>
inline ostream& operator << (ostream& os, pair<T1, T2> p) {
    os << "(" << p.X << "," << p.Y << ")";
    return os;
}

template<class T>
inline ostream& operator << (ostream& os, vector<T> vec) {
    for (auto x : vec) os << x << " ";
    return os;
}

void solve() {
    int n, q; cin >> n >> q;
    
    vector<int> pl(n), wind(q);
    for (auto &x : pl) cin >> x;
    for (auto &x : wind) cin >> x;
    
    vector<pii> maxLR(q+1);
    for (int i = 0, p = 0; i < q; ++i) {
        p += wind[i];
        maxLR[i+1].X = max(maxLR[i].X, -p);
        maxLR[i+1].Y = max(maxLR[i].Y,  p);
    }
    // cout << maxLR << "\n";
    
    vector<pii> snow(n);
    for (int i = 0; i < n-1; ++i) {
        int dist = pl[i+1] - pl[i], lo = 0, hi = q, mi;
        while (lo < hi) {
            mi = lo + hi + 1 >> 1;
            if (maxLR[mi].X + maxLR[mi].Y > dist) hi = mi - 1;
            else lo = mi;
        }
        // cout << dist << " " << lo << "\n";
        if (lo == q) {
            snow[i+1].X = maxLR.back().X;
            snow[i].Y   = maxLR.back().Y;
        }
        else if (maxLR[lo+1].X > maxLR[lo].X) {
            snow[i+1].X = dist - maxLR[lo].Y;
            snow[i].Y   = maxLR[lo].Y;
        }
        else if (maxLR[lo+1].Y > maxLR[lo].Y) {
            snow[i+1].X = maxLR[lo].X;
            snow[i].Y   = dist - maxLR[lo].X;
        }
        // else assert(0);
    }
    snow[0].X = maxLR.back().X, snow[n-1].Y = maxLR.back().Y;
    // cout << snow << "\n";
    
    for (int i = 0; i < n; ++i) cout << snow[i].X + snow[i].Y << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}