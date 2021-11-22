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
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E9;
const int mod = 998244353;

void solve() {
    int n, k;
    cin >> n >> k;
    
    vector<int> t0(n), t1(n);
    
    t0[0] = k-1, t1[0] = k;
    for (int i = 1; i < n; ++i) {
        for (int j = i; j >= 0; --j) {
            t0[j] = (t0[j] + 1) / 2 + (j ? t0[j-1] / 2 : 0);
            t1[j] = (t1[j] + 1) / 2 + (j ? t1[j-1] / 2 : 0);
            // cout << t1[j] << " \n"[j == 0];
        }
    }
    
    for (int i = 0; i <= n; ++i) {
        if (t0[i] ^ t1[i]) {cout << i << "\n"; return;}
    }
}

int32_t main() {
    fastIO();
    
    int t; cin >> t;
    while (t--) solve();
    
    return 0;
}
