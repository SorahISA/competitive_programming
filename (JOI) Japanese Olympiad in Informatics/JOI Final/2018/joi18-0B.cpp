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

int32_t main() {
    fastIO();
    
    int n, tot = 0;
    cin >> n;
    
    vector<pii> v(n), art;
    for (auto &[a, b] : v) cin >> a >> b, tot += b;
    sort(ALL(v));
    
    art.eb(v[0]);
    for (int i = 1; i < n; ++i) {
        if (v[i].X == v[i-1].X) art.back().Y += v[i].Y;
        else art.eb(v[i]);
    }
    tot -= art.back().X - art.front().X;
    
    n = art.size();
    vector<int> pre(n+2), suf(n+2);
    for (int i = 1; i < n; ++i) {
        pre[i] = pre[i-1] + (art[i].X - art[i-1].X) - art[i-1].Y;
    }
    for (int i = n; i > 1; --i) {
        suf[i] = suf[i+1] + (art[i-1].X - art[i-2].X) - art[i-1].Y;
    }
    
    // for (auto x : pre) cout << x << " "; cout << "\n";
    // for (auto x : suf) cout << x << " "; cout << "\n";
    
    for (int i = 1; i < n; ++i) pre[i] = max(pre[i], pre[i-1]);
    for (int i = n; i > 1; --i) suf[i] = max(suf[i], suf[i+1]);
    
    int maxDeleted = 0;
    for (int i = 1; i < n; ++i) maxDeleted = max(maxDeleted, pre[i] + suf[i+2]);
    
    cout << tot + maxDeleted << "\n";
    
    return 0;
}
