#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using vec2d = vector<vector<T>>;
template <typename T>
using vec3d = vector<vec2d<T>>;

// #define X first
// #define Y second
#define eb emplace_back
#define ef push_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    cerr << "\u001b[33m" << "At [" << __FUNCTION__ << "], line " << __LINE__ << ", ",\
    cerr << "(" << #__VA_ARGS__ << ") = ", _do(__VA_ARGS__), cerr << "\u001b[0m"
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int INF = LLONG_MAX >> 2;

int ord(char c) {return c - 'A';}
int lb(int x) {return x & -x;}
int calc(int l1, int all) {int l2=all-l1; return (l1*(l1-1)+l2*(l2-1)) / 2;} /// return twice the answer

void solve() {
    string S; cin >> S;
    int N = SZ(S), G = ord(*max_element(ALL(S))) + 1;
    
    /// initialize ///
    
    vector<int> app[G];
    for (int i = 0; i < N; ++i) app[ord(S[i])].eb(i);
    for (int a = 0; a < G; ++a) app[a].eb(N);
    
    vec3d<int> cnt_LR(G, vec2d<int>(G, vector<int>(N+1, 0))); /// board i across j, [0, k-1] | [k, n-1]
    for (int a = 0; a < G; ++a) {
        for (int b = 0; b < G; ++b) {
            if (a == b) continue;
            vector<int> L(N+1, 0), R(N+1, 0);
            for (int i = 0, c = 0; i < N; ++i) {
                c += ord(S[i]) == b;
                L[i+1] = 2 * c * (ord(S[i]) == a) + L[i]; /// *2
            }
            for (int i = N-1, c = 0; i >= 0; --i) {
                c += ord(S[i]) == b;
                R[i] = 2 * c * (ord(S[i]) == a) + R[i+1]; /// *2
            }
            for (int i = 0; i <= N; ++i) cnt_LR[a][b][i] = L[i] + R[i];
        }
    }
    
    /// start bitmask DP ///
    
    vector<int> dp(1<<G, INF); /// calculate twice the answer
    dp[0] = 0;
    for (int mask = 1; mask < 1<<G; ++mask) {
        for (int i = lb(mask), _m = mask; _m; i = lb(_m ^= i)) {
            int o_i = __lg(i); /// order of (__lg(i))-th char
            
            auto across = [&](int x) -> int {
                int ans = 0;
                for (int o_j = 0; o_j < G; ++o_j) {
                    if ((mask^i) >> o_j & 1) ans += cnt_LR[o_i][o_j][x];
                }
                return ans;
            };
            
            auto get_ans = [&](int x) -> int {
                int ans = dp[mask^i] + across(app[o_i][x]) + calc(x, SZ(app[o_i])-1);
                chmin(dp[mask], ans);
                return ans;
            };
            
            // for (int j = 0; j < SZ(app[o_i]); ++j) get_ans(j);
            
            int lo = 0, hi = SZ(app[o_i]) - 1, mi;
            while (lo < hi) {
                mi = (lo + hi) >> 1;
                if (get_ans(mi) < get_ans(mi+1)) hi = mi;
                else                             lo = mi + 1;
            }
            get_ans(lo);
        }
    }
    
    cout << dp.back() / 2;
    if (dp.back() & 1) cout << "." << dp.back() % 2 * 5;
    cout << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
