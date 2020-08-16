// #pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
// template <typename T>
// using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using pii = pair<int, int>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(1, 7); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 1E6 + 5;

#ifdef local
#define debug(x) for (auto _ : x) cout << _ << " "; cout << "\n";
#else
#define debug(x) ;
#endif

void solve() {
    int N, K, aL, bL, cL, dL, aW, bW, cW, dW, aH, bH, cH, dH;
    cin >> N >> K;
    vector<int> L(K), W(K), H(K);
    for (auto &x : L) cin >> x;
    cin >> aL >> bL >> cL >> dL;
    for (int i = K; i < N; ++i) L.eb((aL * L[i-2] + bL * L[i-1] + cL) % dL + 1);
    for (auto &x : W) cin >> x;
    cin >> aW >> bW >> cW >> dW;
    for (int i = K; i < N; ++i) W.eb((aW * W[i-2] + bW * W[i-1] + cW) % dW + 1);
    for (auto &x : H) cin >> x;
    cin >> aH >> bH >> cH >> dH;
    for (int i = K; i < N; ++i) H.eb((aH * H[i-2] + bH * H[i-1] + cH) % dH + 1);
    
    /// N, L[N], W[N], H[N] ///
    
    vector<int> ans(N, 0);
    ans[0] = 2 * (H[0] + W[0]);
    set<pii> rng;
    rng.insert({-INF, -INF}), rng.insert({ INF,  INF});
    rng.insert({L[0], L[0] + W[0]});
    
    for (int i = 1; i < N; ++i) {
        int l = L[i], r = L[i] + W[i];
        pii hi =      *rng.upper_bound({l, r});
        pii lo = *prev(rng.upper_bound({l, r}));
        ans[i] = ans[i - 1] + 2 * (H[i] + W[i]);
        if (lo.X <= l and r <= lo.Y) {ans[i] = ans[i - 1]; continue;}
        if (lo.Y <  l and r <  hi.X) {rng.insert({l, r}); continue;}
        
        // cout << "\n\n\ni = " << i << "\n\n";
        // cout << "(L, W, H) = " << L[i] << " " << W[i] << " " << H[i] << "\n\n";
        while (1) {
            hi =      *rng.upper_bound({l, r});
            lo = *prev(rng.upper_bound({l, r}));
            // cout << "all rng ";
            // for (auto [x, y] : rng) cout << "(" << x << ", " << y << "),"; cout << "\n";
            // cout << "(l, r, lo.Y, hi.X) = " << l << " " << r << " " << lo.Y << " " << hi.X << "\n";
            if (lo.X <= l and r <= lo.Y) break;
            if (lo.Y <  l and r <  hi.X) break;
            
            if (hi.X <= r) {
                // cout << "r minus " << 2 * (H[i] + min(r, hi.Y) - max(l, hi.X)) << "\n";
                ans[i] -= 2 * (H[i] + min(r, hi.Y) - max(l, hi.X));
                r = max(r, hi.Y), rng.erase(hi);
            }
            if (l <= lo.Y) {
                // cout << "l minus " << 2 * (H[i] + min(r, lo.Y) - max(l, lo.X)) << "\n";
                ans[i] -= 2 * (H[i] + min(r, lo.Y) - max(l, lo.X));
                l = min(l, lo.X), rng.erase(lo);
            }
        }
        rng.insert({l, r});
    }
    
    debug(ans);
    
    int ret = 1;
    for (auto x : ans) ret = ret * (x % mod) % mod;
    cout << ret << "\n";
}

int32_t main() {
    fastIO();
#ifndef local
    freopen("testI.txt", "r", stdin);
    freopen("testO.txt", "w", stdout);
#endif
    
    int t;
    cin >> t;
    for (int _t = 1; _t <= t; ++_t) {
        cout << "Case #" << _t << ": ";
        solve();
    }
    
    return 0;
}
