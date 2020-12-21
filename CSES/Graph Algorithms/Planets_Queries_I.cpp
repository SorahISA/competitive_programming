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

const int maxn = 2E5 + 5;

int anc[maxn][30];

void solve() {
    int n, q; cin >> n >> q;
    
    for (int i = 0; i < n; ++i) cin >> anc[i][0], --anc[i][0];
    
    for (int lay = 1; lay < 30; ++lay) {
        for (int i = 0; i < n; ++i) anc[i][lay] = anc[anc[i][lay-1]][lay-1];
    }
    
    while (q--) {
        int x, k; cin >> x >> k, --x;
        for (int i = 29; i >= 0; --i) {
            if (k >> i & 1) x = anc[x][i];
        }
        cout << x+1 << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
