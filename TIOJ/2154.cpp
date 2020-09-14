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
                 uniform_int_distribution<int> __dis(1E5, 1E6); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E9;
const int mod = 1E9 + 7;
const int maxn = 5E5 + 5;

int32_t main() {
    fastIO();
    
    int n, tmp, ans = (1 << 26) - 1;
    string s;
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        cin >> s, tmp = 0;
        for (auto c : s) tmp |= 1 << (c - 'a');
        ans &= tmp;
    }
    
    if (ans) cout << (char)(__builtin_ctz(ans) + 'a') << "\n";
    else cout << 7122 << "\n";
    
    return 0;
}
