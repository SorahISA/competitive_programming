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
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &x, T y) {return x > y ? x = y, 1 : 0;}
template<typename T> bool chmax(T &x, T y) {return x < y ? x = y, 1 : 0;}

inline void WA() {cout << "impossible\n";}

void solve() {
    int A, B, C, D; cin >> A >> B >> C >> D;
    
    int cnt_0 = (int)floor(sqrt(2*A)) + 1, cnt_1 = (int)floor(sqrt(2*D)) + 1;
    if (A != cnt_0 * (cnt_0 - 1) / 2 or D != cnt_1 * (cnt_1 - 1) / 2) return WA();
    if (!A and !B and !C and !D) return cout << "0\n", void();
    if ( A and !B and !C and !D) return cout << string(cnt_0, '0') << "\n", void();
    if (!A and !B and !C and  D) return cout << string(cnt_1, '1') << "\n", void();
    if (B + C != cnt_0 * cnt_1) return WA();
    
    string ans = string(cnt_0, '0') + string(cnt_1, '1');
    for (int i = cnt_0, tok = 0; i < cnt_0 + cnt_1 and C; ++i, ++tok) {
        if (C >= cnt_0) swap(ans[i], ans[tok]), C -= cnt_0;
        else swap(ans[i], ans[i-C]), C = 0;
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}