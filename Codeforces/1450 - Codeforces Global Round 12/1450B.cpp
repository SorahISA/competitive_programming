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

int dist(pii a, pii b) {
    return abs(a.X - b.X) + abs(a.Y - b.Y);
}

void solve() {
    int n, k; cin >> n >> k;
    
    vector<pii> ball(n);
    for (auto &[x, y] : ball) cin >> x >> y;
    
    int fl = 0;
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = 0; j < n; ++j) cnt += dist(ball[i], ball[j]) <= k;
        fl |= cnt == n;
    }
    cout << (fl ? 1 : -1) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}
