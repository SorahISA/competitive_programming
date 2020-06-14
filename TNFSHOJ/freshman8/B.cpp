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
                 uniform_int_distribution<int> __dis(0, 1); \
                 auto rnd = bind(__dis, __gen);

const int INF = 1E18;
const int mod = 1E9 + 7;

int32_t main() {
    fastIO();
    
    int n, k;
    cin >> n >> k;
    
    vector<int> a(n), b(n), pos;
    for (int i = 0; i < n; ++i) cin >> a[i], k -= a[i];
    for (int i = 0; i < n; ++i) cin >> b[i], pos.eb(b[i] - a[i]);
    
    if (k <= 0) return cout << n << "\n", 0;
    
    sort(ALL(pos));
    for (int i = n-1; i >= 0; --i) {
        if ((k -= pos[i]) <= 0) return cout << i << "\n", 0;
    }
    
    return 0;
}
