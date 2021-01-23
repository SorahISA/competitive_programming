#pragma GCC optimize("O3", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
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
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int maxn = 5000 + 5;

bitset<maxn> dpL[maxn], dpR[maxn];

void solve() {
    int n, k; cin >> n >> k;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    
    dpL[0][0] = 1;
    if (v[0] < k) dpL[0][v[0]] = 1;
    for (int i = 1; i < n; ++i) dpL[i] = dpL[i-1] | (dpL[i-1] << v[i]);
    
    dpR[n-1][0] = 1;
    if (v[n-1] < k) dpR[n-1][v[n-1]] = 1;
    for (int i = n-2; i >= 0; --i) dpR[i] = dpR[i+1] | (dpR[i+1] << v[i]);
    
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        /// dpL[i-1] * dpR[i+1] ///
        if (v[i] >= k) continue;
        int fl = 0;
        if (i == 0) {
            for (int j = k-v[i]; j < k; ++j) fl |= dpR[i+1][j];
        }
        else if (i == n-1) {
            for (int j = k-v[i]; j < k; ++j) fl |= dpL[i-1][j];
        }
        else {
            int sum = 0;
            for (int j = k-v[i]; j < k; ++j) sum += dpR[i+1][j];
            for (int j = 0, L = k-v[i], R = k-1; j < k; ++j) {
                fl |= dpL[i-1][j] & (sum > 0);
                if (L >= 1) sum += dpR[i+1][--L];
                sum -= dpR[i+1][R--];
            }
        }
        cnt += !fl;
    }
    cout << cnt << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}