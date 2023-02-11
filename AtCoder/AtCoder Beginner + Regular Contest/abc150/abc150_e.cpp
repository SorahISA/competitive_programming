#include <bits/stdc++.h>
using namespace std;

#define int int64_t

#define ALL(x) begin(x), end(x)

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int mod = 1'000'000'007;

int fpow(int base, int exp = mod-2, int ans = 1) {
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        exp >>= 1, base = base * base % mod;
    }
    return ans;
}

void solve() {
    int N; cin >> N;
    
    vector<int> C(N);
    for (int &x : C) cin >> x;
    sort(ALL(C));
    
    int ans = 0;
    for (int i = 0; i < N; ++i) ans = (ans + C[i] * (N - i + 1)) % mod;
    cout << ans * fpow(2, 2*N-2) % mod << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
