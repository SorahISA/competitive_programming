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
const int maxn = 1 << 17;

int pre[26][maxn + 5];

int getans(int L, int R, int lay = 0) {
    if (L + 1 == R) return 1 - (pre[lay][R] - pre[lay][L]);
    int M = L + R >> 1;
    return min(getans(L, M, lay + 1) + R - M - (pre[lay][R] - pre[lay][M]),
               getans(M, R, lay + 1) + M - L - (pre[lay][M] - pre[lay][L]));
}

void solve() {
    int n;
    string s;
    cin >> n >> s;
    
    for (char c = 'a'; c <= 'z'; ++c) {
        for (int i = 0; i < n; ++i) {
            pre[c - 'a'][i + 1] = pre[c - 'a'][i] + (s[i] == c);
        }
    }
    
    cout << getans(0, n) << "\n";
}

int32_t main() {
    fastIO();
    
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
