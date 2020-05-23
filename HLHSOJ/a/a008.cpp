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
    
    auto func = [](int x) {
        int i, sum = 0;
        for (i = 1; i*i < x; ++i) sum += (x % i == 0 ? i + x/i : 0);
        if (i * i == x) sum += i;
        return sum - x;
    };
    
    int n, ans;
    while (cin >> n and n) {
        if ((ans = func(n)) == n) cout << "=" << ans << "\n";
        else if (func(ans) == n) cout << ans << "\n";
        else cout << 0 << "\n";
    }
    
    return 0;
}
