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
const int maxn = 1 << 17;

struct Seg {
    int pre, suf, sum, ans;
    Seg(int _pre = 0, int _suf = 0, int _sum = 0, int _ans = 0) :
        pre(_pre), suf(_suf), sum(_sum), ans(_ans) {}
} tree[maxn << 1];

Seg Query(int qL, int qR, int id = 1, int L = 0, int R = maxn-1) {
    if (qR < L or R < qL) return Seg{0, 0, 0, 0};
    if (qL <= L and R <= qR) return Seg{tree[id].pre, tree[id].suf, tree[id].sum, tree[id].ans};
    
    int mi = L + R >> 1;
    Seg ansT;
    Seg ansL = Query(qL, qR, id << 1, L, mi);
    Seg ansR = Query(qL, qR, id << 1 | 1, mi + 1, R);
    
    ansT.pre = max({0LL, ansL.pre, ansL.sum + ansR.pre});
    ansT.suf = max({0LL, ansR.suf, ansL.suf + ansR.sum});
    ansT.sum = ansL.sum + ansR.sum;
    ansT.ans = max({0LL, ansL.ans, ansR.ans, ansL.suf + ansR.pre});
    return ansT;
}

int32_t main() {
    fastIO();
    
    int n, k;
    cin >> n >> k;
    
    for (int i = 0; i < n; ++i) {
        cin >> tree[maxn + i].ans, tree[maxn + i].sum = tree[maxn + i].ans;
        tree[maxn + i].pre = tree[maxn + i].suf = max(0LL, tree[maxn + i].ans);
    }
    
    for (int i = maxn-1; i >= 1; --i) {
        int lt = i << 1, rt = lt | 1;
        tree[i].pre = max({0LL, tree[lt].pre, tree[lt].sum + tree[rt].pre});
        tree[i].suf = max({0LL, tree[lt].suf + tree[rt].sum, tree[rt].suf});
        tree[i].sum = tree[lt].sum + tree[rt].sum;
        tree[i].ans = max({0LL, tree[lt].ans, tree[rt].ans, tree[lt].suf + tree[rt].pre});
    }
    
    int maxAns = 0;
    for (int i = 0, j = k-1; j < n; ++i, ++j) {
        // cerr << setw(2) << i << " : " << setw(2) << Query(i, j).ans << "\n";
        maxAns = max(maxAns, Query(i, j).ans);
    }
    
    cout << maxAns << "\n";
    
    return 0;
}
