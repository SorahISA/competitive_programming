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
    int N, H, W; cin >> N >> H >> W;
    
    vector<pii> vec(N);
    vector<int> all_y;
    for (auto &[x, y] : vec) cin >> x >> y, all_y.eb(y);
    sort(ALL(vec)); /// sort by x-axis
    sort(ALL(all_y)), all_y.resize(unique(ALL(all_y)) - begin(all_y));
    
    int ans = 0;
    for (auto lower_y : all_y) {
        int upper_y = lower_y + H;
        
        vector<int> range_x;
        for (auto [x, y] : vec) {
            if (lower_y <= y and y <= upper_y) range_x.eb(x);
        }
        
        int sz = range_x.size();
        for (int L = 0, R = 0; R < sz; ++L) {
            while (R < sz and range_x[R] - range_x[L] <= W) ++R;
            ans = max(ans, R - L);
        }
    }
    cout << ans << "\n";
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