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

const int INF = 1E18;

void solve() {
    int n; cin >> n;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    
    for (int i = 1; i < n; ++i) {
        if (v[i] < v[i-1]) {cout << 0 << "\n"; return;}
    }
    
    for (int i = 2; i < n; ++i) {
        if (v[i-2] > (v[i-1] ^ v[i])) {cout << 1 << "\n"; return;}
        if ((v[i-2] ^ v[i-1]) > v[i]) {cout << 1 << "\n"; return;}
    }
    
    int minCost = INF;
    for (int i = 0; i < n; ++i) {
        int pre = 0, suf = 0;
        for (int j = i, pre = v[j], op1 = 0; j >= 0; pre ^= v[--j], ++op1) {
            for (int k = i+1, suf = v[k], op2 = 0; k < n; suf ^= v[++k], ++op2) {
                if (pre > suf) minCost = min(minCost, op1 + op2);
            }
        }
    }
    cout << (minCost == INF ? -1 : minCost) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
