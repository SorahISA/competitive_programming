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

const int mod_1 =   998'244'353;
const int mod_2 = 1'000'000'007;
const int p = 257;

int fpow(int base, int exp, int mod, int ans = 1) {
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        exp >>= 1, base = base * base % mod;
    }
    return ans;
}

void solve() {
    int N, M; cin >> N >> M;
    
    int ans = 0;
    unordered_map<int, int> cnt;
    for (int i = 0; i < N; ++i) {
        string S; cin >> S, S += S;
        int top_mul_1 = fpow(p, M, mod_1), hash_1 = 0, max_hash_1 = 0;
        int top_mul_2 = fpow(p, M, mod_2), hash_2 = 0, max_hash_2 = 0;
        for (int j = 0; j < M; ++j) {
            hash_1 = (hash_1 * p + S[j]) % mod_1;
            hash_2 = (hash_2 * p + S[j]) % mod_2;
        }
        for (int j = M; j < 2*M; ++j) {
            hash_1 = (hash_1 * p + S[j]) % mod_1;
            hash_2 = (hash_2 * p + S[j]) % mod_2;
            hash_1 = ((hash_1 - top_mul_1 * S[j]) % mod_1 + mod_1) % mod_1;
            hash_2 = ((hash_2 - top_mul_2 * S[j]) % mod_2 + mod_2) % mod_2;
            chmax(max_hash_1, hash_1);
            chmax(max_hash_2, hash_2);
        }
        ans += cnt[max_hash_1 * mod_2 + max_hash_2]++;
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
