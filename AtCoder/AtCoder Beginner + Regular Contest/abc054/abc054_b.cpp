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
    
    int n, m;
    cin >> n >> m;
    
    vector<string> map1(n), map2(m);
    for (auto &str : map1) cin >> str;
    for (auto &str : map2) cin >> str;
    
    for (int i = 0; i+m <= n; ++i) {
        for (int j = 0; j+m <= n; ++j) {
            int fl = 1;
            for (int di = 0; di < m and fl; ++di) {
                for (int dj = 0; dj < m and fl; ++dj) {
                    if (map1[i+di][j+dj] != map2[di][dj]) fl = 0;
                }
            }
            if (fl) return cout << "Yes\n", 0;
        }
    }
    
    cout << "No\n";
    
    return 0;
}
