#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define A first
#define B second
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<class T1, class T2>
ostream& operator << (ostream &os, pair<T1, T2> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<class T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

void solve() {
    int n, t; cin >> n >> t;
    
    vector<pii> ab(n);
    vector<int> c(n-1);
    for (auto &x : c) cin >> x;
    for (auto &[a, b] : ab) cin >> a;
    for (auto &[a, b] : ab) cin >> b;
    
    auto calculate_greater = [&](int id, int val) -> int {
        int total = 0;
        for (int i = 0; i <= id; ++i) {
            if (ab[i].B == 0 and ab[i].A >= val) return (int)1E10;
            else if (ab[i].A >= val) total += (ab[i].A - val) / ab[i].B + 1;
        }
        return total;
    };
    
    auto linear_sum = [&](int a, int b, int val) -> int {
        /// \sum_{x=0}^{val}{a-bx} ///
        return a * (val + 1) - b * (val * (val + 1) / 2);
    };
    
    auto get_greater_sum = [&](int id, int val) -> int {
        int ret = 0, equal_val = 0, total = 0;
        for (int i = 0; i <= id; ++i) {
            /// A - B * t_max > val ///
            /// A - B * (t_max+1) <= val ///
            if (ab[i].A < val) continue;
            if (ab[i].B == 0) {
                if (ab[i].A > val) assert(0);
                if (ab[i].A == val) equal_val += (int)1E10;
                continue;
            }
            int t_max = (ab[i].A - val) / ab[i].B;
            if (ab[i].A - ab[i].B * t_max == val) --t_max, ++equal_val;
            ret += linear_sum(ab[i].A, ab[i].B, t_max), total += t_max + 1;
        }
        return ret + min(t - total, equal_val) * val;
    };
    
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (i) t -= c[i-1];
        int lo = 0, hi = 1E9 + 5, mi, total;
        while (lo < hi) {
            mi = lo + hi + 1 >> 1;
            total = calculate_greater(i, mi);
            if (total >= t) lo = mi;
            else hi = mi - 1;
        }
        ans = max(ans, get_greater_sum(i, lo));
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1, n; // cin >> t;
    while (t--) solve();
    
    return 0;
}

/*
3 30
0 0
5 7 10
1 2 0

300
*/