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
    int N, K, W, aL, bL, cL, dL, aH, bH, cH, dH;
    cin >> N >> K >> W;
    vector<int> L(K), H(K);
    for (auto &x : L) cin >> x;
    cin >> aL >> bL >> cL >> dL;
    for (int i = K; i < N; ++i) L.eb((aL * L[i-2] + bL * L[i-1] + cL) % dL + 1);
    for (auto &x : H) cin >> x;
    cin >> aH >> bH >> cH >> dH;
    for (int i = K; i < N; ++i) H.eb((aH * H[i-2] + bH * H[i-1] + cH) % dH + 1);
    
    /// N, W, L[N], H[N] ///
    
    vector<int> ans(N, 0);
    ans[0] = 2 * (H[0] + W);
    int sz = 1;
    deque<int> deq = {0}; /// id
    for (int i = 1; i < N; ++i) {
        while (sz >= 2 and min(H[i], H[deq[sz-2]]) >= H[deq.back()]
                       and L[i] <= L[deq[sz-2]] + W) {
            // cout << " p" << deq.back() << "q ";
            --sz, deq.pop_back();
        }
        
        if (L[i] > L[deq.back()] + W) {
            ans[i] = ans[deq.back()] + 2 * (H[i] + W);
        }
        else {
            ans[i] = ans[deq.back()] + 2 * (L[i] - L[deq.back()])
                   + 2 * (H[i] - min(H[i], H[deq.back()]));
        }
        
        ++sz, deq.push_back(i);
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
