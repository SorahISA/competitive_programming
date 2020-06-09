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
    
    int n, m, u, v, ans = 0;
    cin >> n >> m;
    
    int arr[n+5][n+5];
    memset(arr, 0x00, sizeof(arr));
    while (m--) cin >> u >> v, arr[u][v] = arr[v][u] = 1;
    
    int seq[n];
    iota(seq, seq + n, 1);
    
    do {
        int fl = 1;
        for (int i = 1; i < n; ++i) fl &= arr[seq[i-1]][seq[i]];
        ans += fl;
    } while (next_permutation(seq + 1, seq + n));
    
    cout << ans << "\n";
    
    return 0;
}
