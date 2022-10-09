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

/**    x
 *   +-----+
 *   |     |
 * y |     |
 *   |     |
 *   +-----+
**/

int N, M, L;

inline int chk_bf(int x, int y, int top_left) {
    int _x = top_left / N, _y = top_left % N;
    cerr << top_left << ": (" << _x << "+" << x << "," << _y << "+" << y << "): ";
    int sum = 0;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            if (_x + i >= M or _y + j >= N) return cerr << "out of bounds\n", -1;
            sum += (_x + i) * N + (_y + j);
        }
    }
    cerr << sum << "\n";
    return sum;
}

inline bool chk(int x, int y) {
    // cerr << x << " " << y << " ";
    int top_left = (2 * L / (x * y) - (x - 1) - (y - 1) * N) / 2;
    // cerr << top_left << "\n";
    if (top_left * 2 * (x * y) != (2 * L - (x - 1) * (x * y) - (y - 1) * (x * y) * N)) return false;
    if (top_left < 0) return false;
    if ((top_left + x - 1) / N != top_left / N) return false;
    if (top_left / N + y - 1 >= M) return false;
    // assert(chk_bf(y, x, top_left) == L);
    return true;
}

void solve() {
    cin >> M >> N >> L;
    
    vector<int> factors;
    for (int i = 1; i*i <= 2*L; ++i) {
        if (2*L % i == 0) factors.eb(i), factors.eb(2*L / i);
        if (i * i == 2*L) factors.pb();
    }
    sort(ALL(factors));
    
    int ans = INT_MAX;
    for (int x : factors) {
        for (int y : factors) {
            if (x * y * min(x, y) > 2*L) break;
            if (x * y > ans) break;
            if (chk(x, y)) chmin(ans, x * y);
        }
    }
    cout << (ans == INT_MAX ? -1 : ans) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
