/* https://hackmd.io/@joylintp/APCSM_202005 */

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
const int maxn = 1 << 18;

vector<int> lazy(maxn<<1, -1);

void Modify(int L, int R, int C, int nP = 1, int nL = 0, int nR = maxn-1) {
    if (L <= nL and nR <= R) {lazy[nP] = C; return;}
    if (nR < L or R < nL) return;
    if (lazy[nP] != -1) {lazy[nP<<1] = lazy[nP<<1|1] = lazy[nP], lazy[nP] = -1;}
    int mi = nL + nR >> 1;
    Modify(L, R, C, nP<<1  , nL  , mi);
    Modify(L, R, C, nP<<1|1, mi+1, nR);
}

int32_t main() {
    fastIO();
    
    int n, m, l, r, c;
    cin >> n >> m;
    while (m--) cin >> l >> r >> c, Modify(l, r, c);
    for (int i = 1; i <= n; ++i) {
        int pl = i + maxn, col = 0;
        do col = lazy[pl] == -1 ? col : lazy[pl]; while (pl >>= 1);
        cout << col << " \n"[i == n];
    }
    
    return 0;
}
