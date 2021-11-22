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
#define pf pop_front
#define pb pop_back
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

void chmin(int &a, int b) {a = min(a, b);}

const int INF = 3E12;

void solve() {
    int H, W, C; cin >> H >> W >> C;
    
    vector<vector<int>> arr(H, vector<int>(W));
    for (auto &vec : arr) for (auto &x : vec) cin >> x;
    
    int ans = INF;
    vector<vector<int>> min_cost(H, vector<int>(W));
    
    /**
     * Assume the second one is in the bottom-right,
     * calculate minimum cost in its top-left
    **/
    
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            min_cost[i][j] = min(i ? min_cost[i-1][j] : INF,
                                 j ? min_cost[i][j-1] : INF);
            chmin(ans, arr[i][j] + min_cost[i][j] - (H + W - i - j) * C);
            chmin(min_cost[i][j], arr[i][j] + (H + W - i - j) * C);
        }
    }
    
    /**
     * Now assume the second one is in bottom-left,
     * so reverse the array and do it again
    **/
    
    reverse(ALL(arr));
    
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            min_cost[i][j] = min(i ? min_cost[i-1][j] : INF,
                                 j ? min_cost[i][j-1] : INF);
            chmin(ans, arr[i][j] + min_cost[i][j] - (H + W - i - j) * C);
            chmin(min_cost[i][j], arr[i][j] + (H + W - i - j) * C);
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