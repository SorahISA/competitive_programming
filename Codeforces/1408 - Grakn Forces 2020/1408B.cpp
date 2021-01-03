// #pragma GCC target("avx2")
#pragma GCC optimize("Ofast", "unroll-loops")

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
                 uniform_int_distribution<int> __dis(0, 1); \
                 auto rnd = bind(__dis, __gen);

const int INF = 1E18;
const int mod = 1E9 + 7;

void solve() {
    int n, k;
    cin >> n >> k;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    v.resize(unique(ALL(v)) - v.begin());
    
    if (k == 1 and v.size() != 1) {
        cout << -1 << "\n";
        return;
    }
    if (v.size() <= k) {
        cout << 1 << "\n";
        return;
    }
    
    cout << (v.size() - 2) / (k - 1) + 1 << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
