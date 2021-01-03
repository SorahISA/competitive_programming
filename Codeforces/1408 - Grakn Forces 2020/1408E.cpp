// #pragma GCC target("avx2")
#pragma GCC optimize("Ofast", "unroll-loops")

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
const int maxn = 1E5 + 5;

vector<int> p;

int R(int x) {return p[x] ^ x ? p[x] = R(p[x]) : x;}
void U(int x, int y) {p[R(x)] = R(y);}

void solve() {
    int n, m, ans = 0;
    cin >> n >> m, p.resize(n + m + 1), iota(ALL(p), 0);
    
    vector<int> a(n), b(m);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;
    
    vector<pair<int, pii>> allEdge;
    for (int i = 1; i <= n; ++i) {
        int sz, tmp; cin >> sz;
        while (sz--) cin >> tmp, allEdge.eb(a[i-1] + b[tmp-1], pii{i, n+tmp});
    }
    sort(ALL(allEdge), [](auto e1, auto e2) {return e1.X > e2.X;});
    
    for (auto [cost, edge] : allEdge) {
        if (R(edge.X) ^ R(edge.Y)) U(edge.X, edge.Y);
        else ans += cost;
    }
    
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1;
    // cin >> t;
    while (t--) solve();
    
    return 0;
}
