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
    
    vector<int> v;
    for (int len = 3, var = 27; len <= 9; ++len, var *= 3) {
        for (int i = 0; i < var; ++i) {
            int num = 0, base = 1, tmp = i, steps = len;
            int app[3] = {0, 0, 0}, val[3] = {3, 5, 7};
            while (steps--) num += base * val[tmp % 3], app[tmp % 3] = 1, tmp /= 3, base *= 10;
            if (app[0] and app[1] and app[2]) v.eb(num);
        }
    }
    
    int n;
    cin >> n;
    cout << upper_bound(ALL(v), n) - v.begin() << "\n";
    
    return 0;
}
