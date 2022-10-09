#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

#define X first
#define Y second
#define eb emplace_back
#define ef push_front
#define pb pop_back
#define pf pop_front
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

int mypow(int base, int exp, int ans = 1) {
    while (exp) {
        if (exp & 1) ans = ans * base;
        base = base * base, exp >>= 1;
    }
    return ans;
}

void solve_greedy(int W, int C) {
    // int mult[] = {1, 1, 1, 1, 2, 1, 2, 1, 1, 3};
    // int minc[] = {0, 1, 1, 1, 2, 1, 2, 2, 2, 3};
    
    vector<int> minc(100, INT_MAX), mult(100, 0);
    minc[0] = 0, mult[0] = 1;
    for (int x : {1, 2, 3, 5}) {
        for (int i = x; i < 100; ++i) {
            if (minc[i] >  minc[i-x] + 1) minc[i] = minc[i-x] + 1, mult[i] = 0;
            if (minc[i] == minc[i-x] + 1) mult[i] += mult[i-x];
        }
    }
    
    // for (int i : mult | views::take(20)) cerr << i << " ";
    // cerr << "\n";
    // for (int i : minc | views::take(20)) cerr << i << " ";
    // cerr << "\n";
    
    if (W % 1000) return cout << 0 << "\n", void();
    W /= 1000;
    
    int ans = W / mypow(10, C+2) * 20, way = 1;
    W %= mypow(10, C+2);
    while (ans and W / mypow(10, C) < 20) --ans, W += 5 * mypow(10, C);
    way *= mult[(W / mypow(10, C)) % 100];
    ans += minc[(W / mypow(10, C)) % 100];
    for (int i = C-1, val = mypow(10, C-1); i >= 0; --i, val /= 10) {
        way *= mult[(W / val) % 10];
        ans += minc[(W / val) % 10];
    }
    cout << ans << " " << way << "\n";
}

void solve_dp(int W, int C) {
    W /= 1000;
    
    vector<int> trans;
    for (int i = 0; i <= C; ++i) {
        trans.eb(1 * mypow(10, i));
        trans.eb(2 * mypow(10, i));
        trans.eb(3 * mypow(10, i));
        trans.eb(5 * mypow(10, i));
    }
    
    vector<int> dp_min(W+1, INT_MAX), dp_way(W+1, 0);
    dp_min[0] = 0, dp_way[0] = 1;
    for (int x : trans) {
        for (int i = x; i <= W; ++i) {
            if (dp_min[i] >  dp_min[i-x] + 1) dp_min[i] = dp_min[i-x] + 1, dp_way[i] = 0;
            if (dp_min[i] == dp_min[i-x] + 1) dp_way[i] += dp_way[i-x];
        }
    }
    cerr << dp_min[W] << " " << dp_way[W] << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        int W, C; cin >> W >> C;
        solve_greedy(W, C);
        // solve_dp(W, C);
    }
    
    return 0;
}
