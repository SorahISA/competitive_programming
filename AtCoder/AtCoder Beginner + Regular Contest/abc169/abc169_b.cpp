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
    
    int n, fl = 0;
    cin >> n;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x, fl |= x == 0;
    
    if (fl) return cout << 0 << "\n", 0;
    
    double tmp = 0.0;
    for (auto x : v) tmp += log10(x);
    if (tmp > 18.5) return cout << -1 << "\n", 0;
    
    int mult = 1;
    for (auto x : v) mult *= x;
    cout << (mult > INF ? -1 : mult) << "\n";
    
    return 0;
}
