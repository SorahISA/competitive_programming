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

int BIT[maxn];

void Add(int idx, int val) {
    if (idx == 0) return;
    while (idx < maxn) BIT[idx] += val, idx += idx & -idx;
}

int Sum(int idx, int ans = 0) {
    while (idx) ans += BIT[idx], idx -= idx & -idx;
    return ans;
}

int32_t main() {
    fastIO();
    
    int n, q, A, tmp;
    cin >> n >> q >> A;
    
    for (int i = 1; i <= n; ++i) cin >> tmp, Add(i, tmp);
    
    int op, id, w;
    while (q--) {
        cin >> op;
        if (op == 0) {
            int ans = 0, L = 1, R = n;
            while (L <= R) {
                // cout << L << "\n";
                ++ans;
                int lo = 1, hi = maxn, mi, val = 0, goal = A + Sum(L - 1);
                // cout << "goal : " << goal << "\n";
                while (lo < hi) {
                    // cout << lo << " " << hi << "\n";
                    mi = lo + hi >> 1;
                    if (val + BIT[mi] > goal) hi = mi;
                    else lo = mi + 1, val += BIT[mi];
                }
                L = lo;
            }
            cout << ans << "\n";
        }
        else if (op == 1) cin >> id >> w, Add(id,  w);
        else if (op == 2) cin >> id >> w, Add(id, -w);
    }
    
    return 0;
}
