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

const int INF = 0x7f7f7f7f;
const int mod = 1E9 + 7;
const int lgmx = 17;
const int maxn = 1 << 17;

int par[lgmx][maxn];

int Root(int l, int x) {
    return x ^ par[l][x] ? par[l][x] = Root(l, par[l][x]) : x;
}

void Union(int l, int x, int y) {
    par[l][Root(l, x)] = Root(l, y);
}

int32_t main() {
    fastIO();
    
    for (int i = 0; i < lgmx; ++i) {
        iota(par[i], par[i] + maxn, 0);
    }
    
    int n, m;
    cin >> n >> m;
    
    while (m--) {
        int l1, l2, r1, r2, qry;
        cin >> l1 >> r1 >> l2 >> r2, qry = r1 - l1 + 1;
        for (int len = maxn>>1, lay = 0; len; len >>= 1, ++lay) {
            if (qry & len) {
                Union(lay, l1, l2);
                l1 += len, l2 += len, qry -= len;
            }
        }
    }
    
    for (int len = maxn>>2, lay = 0; len; len >>= 1, ++lay) {
        map<int, int> lst_par;
        for (int i = 1; i <= n; ++i) {
            int &lp = lst_par[Root(lay, i)];
            if (lp) {
                Union(lay + 1, lp,       i);
                Union(lay + 1, lp + len, i + len);
            }
            lp = i;
        }
    }
    
    set<int> st;
    for (int i = 1; i <= n; ++i) st.insert(Root(lgmx - 1, i));
    
    int sz = st.size(), ans = 9;
    for (int i = 1; i < sz; ++i) ans = ans * 10 % mod;
    
    cout << ans << "\n";
    
    return 0;
}
