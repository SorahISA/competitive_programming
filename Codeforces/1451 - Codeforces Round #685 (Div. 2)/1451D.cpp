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

inline int check(int a, int b, int c) {
    return a*a + b*b <= c*c;
}

void solve() {
    int k, d;
    cin >> d >> k;
    
    int na = 0, nb = 0;
    while (1) {
             if (check(na+k, nb, d)) na += k;
        else if (check(na, nb+k, d)) nb += k;
        else break;
        
             if (check(na, nb+k, d)) nb += k;
        else if (check(na+k, nb, d)) na += k;
        else break;
    }
    
    cout << (na != nb ? "Ashish" : "Utkarsh") << "\n";
}

int32_t main() {
    fastIO();
    
    int t; cin >> t;
    while (t--) solve();
    
    return 0;
}
