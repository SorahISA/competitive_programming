/* https://hackmd.io/@joylintp/APCSM_202005 */

// #pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

// #define int long long
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
const int maxn = 2E5 + 5;

int parR[maxn], l[maxn], r[maxn], op[maxn], col[maxn];

int R(int x) {
    return parR[x] ^ x ? parR[x] = R(parR[x]) : x;
}

void U(int x, int y) {
    /// x < y ///
    parR[R(x)] = R(y);
}

int32_t main() {
    fastIO();
    iota(parR, parR + maxn, 0);
    memset(col, 0xff, sizeof(col));
    
    int n, m;
    cin >> n >> m;
    
    for (int i = 1; i <= m; ++i) cin >> l[i] >> r[i] >> op[i];
    
    for (int i = m; i >= 1; --i) {
        for (int now = l[i]; now <= r[i];) {
            if (col[now] == -1) {
                col[now] = op[i];
                if (col[now-1] != -1) U(now - 1, now);
                if (col[now+1] != -1) U(now, now + 1);
            }
            now = R(now) + 1;
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        cout << (col[i] == -1 ? 0 : col[i]) << " \n"[i == n];
    }
    
    return 0;
}
