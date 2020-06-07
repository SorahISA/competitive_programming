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
    int a, b;
    cin >> a >> b;
    if (a > b) swap(a, b);
    
    if (b - a <= 1) {cout << 2*a - 2 << "\n"; return;}
    
    int c = floor(sqrt(a*b + 0.1));
    if (c * c == a * b) --c;
    if (c * (c + 1) >= a * b) cout << 2*c - 2 << "\n";
    else cout << 2*c - 1 << "\n";
}

int32_t main() {
    fastIO();
    
    int q;
    cin >> q;
    while (q--) solve();
    
    return 0;
}
