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
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

void solve() {
    cout.setf(ios_base::fixed);
    cout.precision(9);
    
    int Q; cin >> Q;
    
    int op, x = 0;
    vector<int> pre{0};
    
    while (Q--) {
        cin >> op;
        if (op == 1) cin >> x, pre.eb(pre.back() + x);
        else if (op == 2 and pre.size() == 2) cout << 0.0 << "\n";
        else {
            int lo = 1, hi = pre.size()-2, milo, mihi;
            while (lo < hi) {
                milo = (lo + lo + hi) / 3;
                mihi = (lo + hi + hi + 2) / 3;
                if (1.0 * (pre[milo] + x) / (milo + 1) > 1.0 * (pre[mihi] + x) / (mihi + 1)) lo = milo + 1;
                else                                                                         hi = mihi - 1;
            }
            cout << x - 1.0 * (pre[lo] + x) / (lo + 1) << "\n";
        }
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}