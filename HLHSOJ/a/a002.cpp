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
    
    vector<int> v{10, 11, 12, 13, 14, 15, 16, 17, 34, 18,
                  19, 20, 21, 22, 35, 23, 24, 25, 26, 27,
                  28, 29, 32, 30, 31, 33};
    
    int n;
    while (cin >> n) {
        for (int c = 0; c < 26; ++c) {
            int ans = 0, val = 1000000000LL * v[c] + n;
            for (int i = 1; i <= 9; ++i) val /= 10, ans += (val % 10) * i;
            ans += val / 10;
            
            if ((10 - ans % 10) % 10 == n % 10) cout << (char)(c + 65);
        }
        cout << "\n";
    }
    
    return 0;
}
