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
                 uniform_int_distribution<int> __dis(1, 7); \
                 auto rnd = bind(__dis, __gen)

#define ls(x) ((x) << 1)
#define rs(x) ((x) << 1 | 1)

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 1 << 20;

int BIT[2][maxn], cnt[maxn];

void Add(int tp, int idx, int val) {
    while (idx < maxn) BIT[tp][idx] += val, idx += idx & -idx;
}

int Sum(int tp, int idx, int ans = 0) {
    if (idx == maxn) --idx;
    while (idx) ans += BIT[tp][idx], idx -= idx & -idx;
    return ans;
}

pii BinarySearch(int k) {
    int lo = 1, hi = maxn, mi, val = 0;
    while (lo < hi) {
        mi = lo + hi >> 1;
        if (val + BIT[0][mi] >= k) hi = mi;
        else lo = mi + 1, val += BIT[0][mi];
    }
    return {lo, val + cnt[lo] - k};
}

int32_t main() {
    fastIO();
    
    int n, k, m, ans = 0;
    cin >> n >> k >> m;
    
    vector<pii> ins[n + 5], del[n + 5];
    
    for (int i = 1; i <= m; ++i) {
        int l, r, c, p;
        cin >> l >> r >> c >> p;
        ins[l].eb(c, p), del[r + 1].eb(c, p);
    }
    
    for (int i = 1; i <= n; ++i) {
        for (auto [c, p] : ins[i]) {
            Add(0, p,    c); /// INS count
            Add(1, p,  p*c); /// INS cost to buy everything <= p
            cnt[p] += c;
        }
        for (auto [c, p] : del[i]) {
            Add(0, p,   -c); /// DEL count
            Add(1, p, -p*c); /// DEL cost to buy everything <= p
            cnt[p] -= c;
        }
        
        auto [maxAll, left] = BinarySearch(k); /// find k'th min and delete leftover
        ans += Sum(1, maxAll) - max(0LL, maxAll * left);
    }
    
    cout << ans << "\n";
    
    return 0;
}
