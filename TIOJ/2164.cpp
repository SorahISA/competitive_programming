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
const int maxn = 5E3 + 5;

int x[maxn], y[maxn], z[maxn], dis[maxn], in[maxn];

inline int get_dis(int p1, int p2) {
    return (x[p1] - x[p2]) * (x[p1] - x[p2])
         + (y[p1] - y[p2]) * (y[p1] - y[p2])
         + (z[p1] - z[p2]) * (z[p1] - z[p2]);
}

int32_t main() {
    fastIO();
    
    int n, ans = 0;
    cin >> n;
    
    memset(dis, 0x7f, sizeof(dis));
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i] >> z[i];
    
    in[0] = 1;
    for (int i = 0; i < n; ++i) {
        dis[i] = min(dis[i], get_dis(0, i));
    }
    
    for (int i = 1; i < n; ++i) {
        int minId = -1;
        for (int j = 0; j < n; ++j) {
            if (in[j] == 0 and (minId == -1 or dis[j] < dis[minId])) minId = j;
        }
        in[minId] = 1, ans += dis[minId];
        for (int j = 0; j < n; ++j) {
            dis[j] = min(dis[j], get_dis(minId, j));
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
