#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At func [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int mod = 1'000'000'007;

void solve() {
    int N, M, L, R, K; cin >> N >> M >> L >> R >> K;
    K = ((K - N%M * L) % M + M) % M, R -= L;
    
    /// 0 <= a_i <= R and sum(a_i) % M == K ///
    
    auto mul = [&](vector<int> A, vector<int> B) -> vector<int> {
        vector<int> C(M, 0);
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < M; ++j) {
                C[i+j>=M ? i+j-M : i+j] += A[i] * B[j] % mod;
            }
        }
        for (int &c : C) c %= mod;
        return C;
    };
    
    vector<int> ans(M, 0), base(M, 0);
    ans[0] = 1;
    for (int i = 0; i < M; ++i) base[i] = R / M + (R % M >= i);
    
    while (N) {
        if (N & 1) ans = mul(ans, base);
        N >>= 1, base = mul(base, base);
    }
    
    cout << ans[K] << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
