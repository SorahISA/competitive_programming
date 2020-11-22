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
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 2E5 + 5;

void solve() {
    int n, k;
    string s, t;
    cin >> n >> k >> s >> t;
    
    vector<int> cnt_s(26), cnt_t(26);
    for (auto c : s) ++cnt_s[c - 'a'];
    for (auto c : t) ++cnt_t[c - 'a'];
    
    int fl = 1;
    for (int i = 0; i < 26; ++i) {
        if (cnt_s[i] < cnt_t[i]) fl = 0;
        if (cnt_s[i] > cnt_t[i]) {
            if ((cnt_s[i] - cnt_t[i]) % k) fl = 0;
            else if (i != 25) cnt_s[i+1] += cnt_s[i] - cnt_t[i];
        }
    }
    
    cout << (fl ? "Yes" : "No") << "\n";
}

int32_t main() {
    fastIO();
    
    int t; cin >> t;
    while (t--) solve();
    
    return 0;
}
