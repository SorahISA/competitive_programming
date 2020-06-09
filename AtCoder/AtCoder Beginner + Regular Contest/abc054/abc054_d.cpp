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
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

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

const int INF = 1E18;
const int mod = 1E9 + 7;

int32_t main() {
    fastIO();
    
    int n, ma, mb, lhf, rhf;
    cin >> n >> ma >> mb, lhf = n / 2, rhf = n - lhf;
    
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) cin >> a[i] >> b[i] >> c[i];
    
    vector<int> la(1 << lhf, 0), lb(1 << lhf, 0), lc(1 << lhf, 0);
    for (int i = 1; i < (1<<lhf); ++i) {
        for (int j = 0; j < lhf; ++j) {
            if (i >> j & 1) la[i] += a[j], lb[i] += b[j], lc[i] += c[j];
        }
    }
    
    vector<int> ra(1 << rhf, 0), rb(1 << rhf, 0), rc(1 << rhf, 0);
    for (int i = 1; i < (1<<rhf); ++i) {
        for (int j = 0; j < rhf; ++j) {
            if (i >> j & 1) ra[i] += a[lhf+j], rb[i] += b[lhf+j], rc[i] += c[lhf+j];
        }
    }
    
    map<pii, int> lminC, rminC;
    for (int i = 1; i < (1<<lhf); ++i) {
        if (!lminC[{la[i], lb[i]}]) lminC[{la[i], lb[i]}] = lc[i];
        else lminC[{la[i], lb[i]}] = min(lminC[{la[i], lb[i]}], lc[i]);
    }
    for (int i = 1; i < (1<<rhf); ++i) {
        if (!rminC[{ra[i], rb[i]}]) rminC[{ra[i], rb[i]}] = rc[i];
        else rminC[{ra[i], rb[i]}] = min(rminC[{ra[i], rb[i]}], rc[i]);
    }
    
    int ans = INF;
    for (auto ab : lminC) {
        if (ab.X.X * mb == ab.X.Y * ma) ans = min(ans, ab.Y);
        else {
            for (int amount = 1; amount <= 400; ++amount) {
                if (ab.X.X > amount * ma or ab.X.Y > amount * mb) continue;
                if (rminC[{amount*ma - ab.X.X, amount*mb - ab.X.Y}]) {
                    ans = min(ans, ab.Y + rminC[{amount*ma - ab.X.X, amount*mb - ab.X.Y}]);
                }
            }
        }
    }
    for (auto ab : rminC) {
        if (ab.X.X * mb == ab.X.Y * ma) ans = min(ans, ab.Y);
    }
    
    cout << (ans == INF ? -1 : ans) << "\n";
    
    return 0;
}
