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

int32_t main() {
    fastIO();
    
    int d, goal;
    cin >> d >> goal, goal /= 100;
    
    vector<pii> prob(d);
    for (auto &x : prob) cin >> x.X >> x.Y, x.Y /= 100;
    
    int ans = INF;
    for (int i = 0; i < (1<<d); ++i) {
        int probs = 0, score = 0;
        for (int j = 0; j < d; ++j) {
            if (i >> j & 1) {
                probs += prob[j].X;
                score += prob[j].X * (j + 1) + prob[j].Y;
            }
        }
        for (int j = d-1; j >= 0 and score < goal; --j) {
            if (~i >> j & 1) {
                probs += min(prob[j].X, (goal - score - 1) / (j + 1) + 1);
                score += min(prob[j].X, (goal - score - 1) / (j + 1) + 1) * (j + 1);
            }
        }
        ans = min(ans, probs);
    }
    
    cout << ans << "\n";
    
    return 0;
}
