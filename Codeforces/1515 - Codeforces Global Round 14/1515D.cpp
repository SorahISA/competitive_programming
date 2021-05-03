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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % (uint64_t)(R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

void solve() {
    int n, l, r; cin >> n >> l >> r;
    
    map<int, int> cl, cr;
    for (int i = 0; i < l; ++i) {
        int tmp; cin >> tmp, ++cl[tmp];
    }
    for (int i = 0; i < r; ++i) {
        int tmp; cin >> tmp, ++cr[tmp];
    }
    
    for (auto [key, val] : cl) {
        int succ = min(cl[key], cr[key]);
        cl[key] -= succ, cr[key] -= succ;
    }
    
    int cntL1 = 0, cntL2 = 0, cntR1 = 0, cntR2 = 0;
    for (auto [key, val] : cl) cntL1 += val & 1, cntL2 += val / 2;
    for (auto [key, val] : cr) cntR1 += val & 1, cntR2 += val / 2;
    
    if (cntL1 + 2 * cntL2 == cntR1 + 2 * cntR2) return cout << cntL1 + 2 * cntL2 << "\n", void();
    if (cntL1 + 2 * cntL2 < cntR1 + 2 * cntR2) swap(cntL1, cntR1), swap(cntL2, cntR2);
    
    int ans = 0, cntR = cntR1 + 2 * cntR2;
    ans = min(cntR, cntL1), cntR -= ans, cntL1 -= ans;
    if (cntR == 0) {
        cout << ans + cntL1 + cntL2 << "\n";
    }
    else {
        ans += cntR, cntL2 -= cntR / 2, cntR = 0;
        cout << ans + cntL2 << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}