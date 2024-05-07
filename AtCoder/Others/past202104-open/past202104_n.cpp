#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define ef push_front
#define pf pop_front
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template <typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int C = 1e5;

void solve() {
    int N, H;
    cin >> N >> H;
    vector<pii> inp(N);
    vector<int> dp(C + H + 1, -1);
    dp[C + H] = 0;
    for(int i = 0; i < N; i++) {
        cin >> inp[i].X >> inp[i].Y;
    }
    sort(ALL(inp), [&](pii a, pii b){
        return a.X * b.Y > b.X * a.Y; 
    });
    for(int _ = 0; _ < N; _++) {
        int v = inp[_].X, w = inp[_].Y;
        for(int i = C - w + 1; i <= C + H - w; i++) {
        // for(int i = C + H - w; i + w > C; i--) {
            if(dp[i + w] != -1) {
                dp[i] = max(dp[i], dp[i + w] + (i + w - C) * v); 
            } 
        }
    }
    int ans = 0;
    for(int i = 0; i <= C + H; i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans << '\n';
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
