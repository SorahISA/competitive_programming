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

const int INF = 1E9;
const int mod = 1E9 + 7;

int32_t main() {
    fastIO();
    
    int a, b, c, d, e, f, cnt = 0;
    cin >> a >> b >> c >> d >> e >> f;
    
    if (!(a | b | c | d | e | f)) return cout << "Too many... = =\"\n", 0;
    
    auto func = [&](int x) {
        return a*x*x*x*x*x + b*x*x*x*x + c*x*x*x + d*x*x + e*x + f;
    };
    
    for (int i = -36; i <= 36; ++i) {
        if (func(i) == 0) ++cnt, cout << i << " " << i << "\n";
        if (func(i) < 0 and func(i+1) > 0) ++cnt, cout << i << " " << i+1 << "\n";
        if (func(i) > 0 and func(i+1) < 0) ++cnt, cout << i << " " << i+1 << "\n";
    }
    
    if (!cnt) cout << "N0THING! >\\\\\\<\n";
    
    return 0;
}
