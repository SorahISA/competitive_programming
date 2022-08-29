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

void solve() {
    int n, m, minAns = INF, fl = 0; /// can't reach
    cin >> n >> m;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    
    if (m >= n - 1) minAns = 0;
    
    deque<pii> deq;
    deq.push_back({0, 0});
    for (int i = 1; i < n-1; ++i) {
        if (v[i]) {
            int ans = (deq.empty() ? 0 : deq.front().Y) + v[i];
            while (!deq.empty() and deq.back().Y >= ans) deq.pop_back();
            deq.push_back({i, ans});
            if (i >= n - m - 1) minAns = min(minAns, ans);
        }
        if (deq.front().X == i - m) deq.pop_front();
        if (deq.empty()) fl = 1;
    }
    
    cout << (fl ? -1 : minAns) << "\n";
}

int32_t main() {
    fastIO();
#ifndef local
    freopen("testI.txt", "r", stdin);
    freopen("testO.txt", "w", stdout);
#endif
    
    int t;
    cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        cout << "Case #" << tc << ": ";
        solve();
    }
    
    return 0;
}
