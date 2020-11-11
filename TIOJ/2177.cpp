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

// #define X first
// #define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E9;
const int mod = 998244353;

struct Problem {
    int Q, D, X;
};

int32_t main() {
    fastIO();
    
    int n, m;
    cin >> n >> m;
    
    vector<int> a(m+1);
    for (int i = 1; i <= m; ++i) cin >> a[i];
    
    vector<Problem> prob(n);
    for (auto &p : prob) cin >> p.Q >> p.D >> p.X;
    sort(ALL(prob), [](auto p1, auto p2) {return p1.D < p2.D;});
    
    vector<int> dp(n);
    for (int i = 0; i < n; ++i) {
        dp[i] = max(0LL, prob[i].Q);
        for (int j = 0; j < i; ++j) {
            dp[i] = max(dp[i], dp[j] + prob[i].Q - (prob[i].X == prob[j].X) * a[prob[i].X]);
        }
    }
    
    cout << *max_element(ALL(dp)) << "\n";
    
    return 0;
}
