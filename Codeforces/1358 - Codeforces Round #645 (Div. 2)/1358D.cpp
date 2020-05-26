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

int getSum(int H, int len) {
    int L = H - len;
    return (H * (H + 1) / 2) - (L * (L + 1) / 2);
}

int32_t main() {
    fastIO();
    
    int n, len;
    cin >> n >> len;
    
    vector<int> v(2*n), hug(2*n, 0);
    for (int i = 0; i < n; ++i) cin >> v[i], v[n+i] = v[i];
    reverse(ALL(v));
    
    for (int i = 0; i < 2*n; ++i) hug[i] = v[i] * (v[i] + 1) / 2;
    
    int days = 0, hugs = 0, maxAns = 0;
    for (int L = 0, R = 0; L < n; ++L) {
        while (days + v[R] < len) days += v[R], hugs += hug[R], ++R;
        // cout << "L : " << L << " , " << days << " , " << hugs << "\n";
        maxAns = max(maxAns, hugs + getSum(v[R], len - days));
        days -= v[L], hugs -= hug[L];
    }
    
    cout << maxAns << "\n";
    
    return 0;
}
