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
                 uniform_int_distribution<int> __dis(1, 1E13); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 5E5 + 5;

int32_t main() {
    fastIO();
    RANDOM();
    
    for (int i = 0; i < 7; ++i) rnd();
    
    int n;
    cin >> n;
    
    vector<int> v(n);
    map<int, int> cnt, mapping, prefix_cnt;
    map<int, deque<int>> deq;
    int right = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        auto &x = v[i];
        cin >> x;
        if (mapping[x] == 0) mapping[x] = rnd();
        x = mapping[x];
        auto _x = x;
        if (++cnt[x] % 3 == 0) x = -2 * x;
        if (i) x += v[i - 1];
        deq[_x].eb(i);
        if (deq[_x].size() > 3) {
            while (right < deq[_x].front()) --prefix_cnt[v[right++]];
            deq[_x].pop_front();
        }
        // cout << "right " << right << "\n";
        // for (auto [key, val] : prefix_cnt) cout << "--> (" << key << ", " << val << ")\n";
        // cout << "plus " << prefix_cnt[x] + (right == 0 and x == 0) << "\n";
        ans += prefix_cnt[x] + (right == 0 and x == 0);
        ++prefix_cnt[x];
    }
    
    // cout << "v : [ ";
    // for (auto x : v) cout << x << " ";
    // cout << "]\n";
    
    cout << ans << "\n";
    
    return 0;
}
