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


void solve() {
    int N, M; cin >> N >> M;
    map<int, vector<int>> y_axis;
    
    for (int i = 0; i < M; ++i) {
        int x, y; cin >> x >> y;
        if (abs(y-N) <= M) y_axis[x].eb(y);
    }
    
    set<int> ans{N};
    for (auto [x, vec_y] : y_axis) {
        vector<int> add;
        for (auto y : vec_y) {
            if (ans.count(y-1) or ans.count(y+1)) add.eb(y);
        }
        for (auto y : vec_y) ans.erase(y);
        for (auto y : add) ans.insert(y);
    }
    cout << ans.size() << "\n";
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