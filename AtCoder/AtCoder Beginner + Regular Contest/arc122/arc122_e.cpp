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

void lcm_check(int &x, int y, int chk) {
#ifdef local
#define __int128 int64_t
#endif
    __int128 _x = x, _y = y, _chk = chk;
    _x = _x * _y / __gcd(_x, _y);
    x = _x >= _chk ? (int)-1 : _x;
}

void solve() {
    int N; cin >> N;
    
    vector<int> arr(N), ans;
    for (auto &x : arr) cin >> x;
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N-i; ++j) {
            int lcm = 1, fl = 1;
            for (int k = 0; k < N-i and fl; ++k) {
                if (j == k) continue;
                lcm_check(lcm, __gcd(arr[j], arr[k]), arr[j]);
                // if (lcm >= arr[j]) fl = 0;
                if (lcm == -1) fl = 0;
            }
            if (fl) {ans.eb(arr[j]), arr.erase(begin(arr) + j); break;}
        }
    }
    
    if (ans.size() != N) cout << "No\n";
    else reverse(ALL(ans)), cout << "Yes\n" << ans << "\n";
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