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

void solve() {
    int n;
    string is, os;
    cin >> n >> is >> os;
    
    int reach[n][n];
    memset(reach, 0x00, sizeof(reach));
    
    for (int i = 0; i < n; ++i) {
        reach[i][i] = 1;
        for (int j = i+1; j < n; ++j) {
            if (os[j - 1] == 'Y' and is[j] == 'Y') reach[i][j] = 1;
            else break;
        }
        for (int j = i-1; j >= 0; --j) {
            if (os[j + 1] == 'Y' and is[j] == 'Y') reach[i][j] = 1;
            else break;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cout << "NY"[reach[i][j]];
        cout << "\n";
    }
}

int32_t main() {
    fastIO();
#ifndef local
    freopen("testI.txt", "r", stdin);
    freopen("testO.txt", "w", stdout);
#endif
    
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        cout << "Case #" << tc << ":\n";
        solve();
    }
    
    return 0;
}
