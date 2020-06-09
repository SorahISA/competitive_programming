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

int len[55], cnt[55], ans = 0;

void recur(int lay, int left) {
    if (left == len[lay]) {ans += cnt[lay]; return;}
    if (left <= 1) return;
    if (left < len[lay-1] + 1) recur(lay - 1, left - 1);
    else {
        ans += cnt[lay-1] + (left >= len[lay-1] + 2);
        recur(lay - 1, left - len[lay-1] - 2);
    }
}

int32_t main() {
    fastIO();
    
    len[0] = 1, cnt[0] = 1;
    for (int i = 1; i < 55; ++i) {
        len[i] = 2 * len[i-1] + 3;
        cnt[i] = 2 * cnt[i-1] + 1;
    }
    
    int n, x;
    cin >> n >> x;
    
    recur(n, x);
    
    cout << ans << "\n";
    
    return 0;
}
