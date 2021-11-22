#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T> using Prior = std::priority_queue<T>;
template<typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &x, T y) {return x > y ? x = y, 1 : 0;}
template<typename T> bool chmax(T &x, T y) {return x < y ? x = y, 1 : 0;}

const int maxn = 100 + 5;
const int maxw = 100 + 5;
    
bitset<maxn * maxw> cover;

void solve() {
    int N, H, W; cin >> N >> H >> W;
    
    for (int i = 0, x; i < N; ++i) {
        cin >> x;
        if (i & 1) x = -x;
        for (int j = 0; j < W; ++j) cover[i*W+j+x] = 1;
    }
    
    int ans = 0;
    for (int i = 0; i < N*W; ++i) ans += !cover[i];
    cout << ans * H << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}