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
    os << p.first << " " << p.second;
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << "\n";
        os << vec[i];
    }
    return os;
}

void solve() {
    vector<int> coeff(6);
    vector<pii> sol;
    
    for (auto &x : coeff) cin >> x;
    
    auto calc = [&](int x) {
        int ans = 0;
        for (int i = 0; i < 6; ++i) ans = ans * x + coeff[i];
        return ans;
    };
    
    /// 36^6 > 2147483647 ///
    for (int num = -36; num <= 35; ++num) {
        if (calc(num) == 0) sol.eb(num, num);
        else if (calc(num+1) != 0 and (calc(num) > 0) ^ (calc(num+1) > 0)) sol.eb(num, num+1);
    }
    
         if (sol.size() == 0) cout << "N0THING! >\\\\\\<\n";
    else if (sol.size() > 5) cout << "Too many... = =\"\n";
    else cout << sol << "\n";
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