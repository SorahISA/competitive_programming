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

const int maxn = 1E4 + 50;

short cnt[maxn][maxn];

int getlen(int r, int a) {
    /// r*r = a*a + b*b ///
    /// b = sqrt(r*r - a*a) ///
    return floor(sqrt(r*r - a*a) + 1e-5);
}

int32_t main() {
    fastIO();
    
    // for (int i = 0; i < maxn; ++i) cnt[i].insert({-maxn, -maxn});
    
    int n, m;
    cin >> n;
    
    vector<pii> pt(n);
    for (auto &[x, y] : pt) cin >> x >> y;
    
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y, r;
        cin >> x >> y >> r;
        for (int j = max(0LL, y-r); j <= min(10000LL, y+r); ++j) {
            int len = getlen(r, abs(y - j));
            // cnt[j].insert({x - len, x + len});
            ++cnt[j][max(0LL, x - len)];
            --cnt[j][min(10001LL, x + len + 1)];
            // cout << "? " << j << " " << x-len << " " << x+len << "\n";
        }
    }
    
    for (int i = 0; i < maxn; ++i) {
        partial_sum(cnt[i], cnt[i] + maxn, cnt[i]);
    }
    
    int ans = n;
    for (auto [x, y] : pt) {
        if (cnt[y][x]) --ans;
    }
    
    cout << ans << "\n";
    
    return 0;
}