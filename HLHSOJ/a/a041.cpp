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
                 uniform_int_distribution<int> __dis(0, 1); \
                 auto rnd = bind(__dis, __gen);

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 1 << 16;

pii seg[maxn << 1]; // [MAX, MIN]

int32_t main() {
    fastIO();
    
    int n, q, L, R;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> seg[maxn+i].first, seg[maxn+i].second = seg[maxn+i].first;
    for (int i = maxn-1; i >= 1; --i) seg[i].first = max(seg[i<<1].first, seg[i<<1|1].first);
    for (int i = maxn-1; i >= 1; --i) seg[i].second = min(seg[i<<1].second, seg[i<<1|1].second);
    
    while (q--) {
        cin >> L >> R, L += maxn - 1, R += maxn - 1;
        
        int maxV = max(seg[L].first, seg[R].first), minV = min(seg[L].second, seg[R].second);
        while (L ^ R ^ 1) {
            if (L == R) break;
            if (~L & 1) maxV = max(maxV, seg[L^1].first), minV = min(minV, seg[L^1].second);
            if ( R & 1) maxV = max(maxV, seg[R^1].first), minV = min(minV, seg[R^1].second);
            L >>= 1, R >>= 1;
        }
        
        cout << maxV - minV << "\n";
    }
    
    return 0;
}
