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

const int maxn = 2500 + 5;

int BIT[maxn];

void Add(int idx, int val = 1) {
    while (idx < maxn) BIT[idx] += val, idx += idx & -idx;
}

int Sum(int idx, int ans = 0) {
    while (idx) ans += BIT[idx], idx -= idx & -idx;
    return ans;
}

int Query(int L, int R) {
    return Sum(R) - Sum(L-1);
}

void solve() {
    int n; cin >> n;
    
    vector<int> allY;
    vector<pii> cow(n);
    for (auto &c : cow) cin >> c.X >> c.Y, allY.eb(c.Y);
    sort(ALL(cow)), sort(ALL(allY));
    for (auto &c : cow) c.Y = lower_bound(ALL(allY), c.Y) - allY.begin();
    
    int ans = n+1;
    for (int i = 0; i < n; ++i) {
        Add(cow[i].Y+1);
        for (int j = i+1; j < n; ++j) {
            Add(cow[j].Y+1);
            ans += Query(1, min(cow[i].Y, cow[j].Y)+1)
                 * Query(max(cow[i].Y, cow[j].Y)+1, n);
            // cout << i << " " << j << ": " << ans << "\n";
        }
        for (int j = i; j < n; ++j) Add(cow[j].Y+1, -1);
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
