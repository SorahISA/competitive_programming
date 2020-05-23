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
    int n, cost[6], d;
    cin >> n >> cost[2] >> cost[3] >> cost[5] >> d;
    
    map<int, int> ans;
    Prior<int> que; que.push(n);
    
    int lst = -1;
    while (!que.empty()) {
        int nxt = que.top(); que.pop();
        if (nxt == lst) continue;
        lst = nxt;
        // cout << "on " << nxt << " : " << ans[nxt] << "\n";
        
        for (auto x : {2, 3, 5}) {
            ans[ nxt     /x] = min((ans[ nxt     /x] ? ans[ nxt     /x] : INF),
                                   ans[nxt] + (nxt > 2E9 ? INF : (nxt -  nxt     /x) * d));
            ans[(nxt+x-1)/x] = min((ans[(nxt+x-1)/x] ? ans[(nxt+x-1)/x] : INF),
                                   ans[nxt] + (nxt > 2E9 ? INF : (nxt - (nxt+x-1)/x) * d));
            ans[ nxt     /x] = min(ans[ nxt     /x], ans[nxt] + cost[x] + (  nxt%x)   * d);
            ans[(nxt+x-1)/x] = min(ans[(nxt+x-1)/x], ans[nxt] + cost[x] + (x-nxt%x)%x * d);
            // cout << "  push " <<  nxt     /x << " : " << ans[ nxt     /x] << "\n";
            // cout << "  push " << (nxt+x-1)/x << " : " << ans[(nxt+x-1)/x] << "\n";
            que.push(nxt/x), que.push((nxt+x-1)/x);
        }
        
        if (nxt == 0) break;
    }
    
    // for (int i = 0; i <= 11; ++i) cout << ans[i] << " \n"[i == 11];
    
    cout << ans[0] << "\n";
}

int32_t main() {
    fastIO();
    
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}