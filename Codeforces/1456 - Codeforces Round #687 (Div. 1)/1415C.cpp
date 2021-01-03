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

const int INF = 1E9;

void solve() {
    int n, p, k, x, y;
    string s;
    cin >> n >> p >> k >> s >> x >> y;
    
    vector<int> add(n);
    for (int i = n-1; i >= 0; --i) {
        add[i] = (i+k < n ? add[i+k] : 0LL) + (s[i] == '0');
    }
    
    // for (auto _ : add) cout << _ << " "; cout << "\n";
    
    int ans = INF;
    for (int i = p-1, del = 0; i < n; ++i, ++del) {
        ans = min(ans, add[i] * x + del * y);
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}
