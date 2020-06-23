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

const int INF = 1E12;
const int mod = 1E9 + 7;

int fastpow(int base, int exp) {
    int ans = 1;
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return ans;
}

void ADD(int &a, int b) {a = ((a + b) % mod + mod) % mod;}
void SUB(int &a, int b) {a = ((a - b) % mod + mod) % mod;}

void solve() {
    int n, p, winA = 0, diff = 0;
    cin >> n >> p;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    sort(ALL(v), [](auto a, auto b) {return a > b;});
    
    if (p == 1) {cout << (n & 1) << "\n"; return;}
    
    int fl = 0, lst = v[0]; /// win too much (>= 1e12)
    for (auto x : v) {
        while (lst > x and !fl) {
            if (!winA) {lst = x; break;}
            if (lst - x >= 40 and winA) {fl = 1; break;}
            --lst, winA *= p;
            if (winA >= INF) fl = 1;
        }
        
        if (winA or fl) --winA, SUB(diff, fastpow(p, x));
        else ++winA, ADD(diff, fastpow(p, x));
    }
    
    cout << diff << "\n";
}

int32_t main() {
    fastIO();
    
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
