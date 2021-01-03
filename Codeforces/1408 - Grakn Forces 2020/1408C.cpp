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
const double eps = 1e-7;

void solve() {
    int n, l;
    cin >> n >> l;
    
    deque<double> fl(n);
    for (auto &x : fl) cin >> x;
    fl.push_front(0), fl.push_back(l);
    n += 2;
    
    vector<double> tA(n), tB(n);
    for (int i = 1; i <= n-1; ++i) {
        /// speed_A = i ///
        tA[i] = tA[i-1] + (fl[i] - fl[i-1]) / i;
    }
    for (int i = n-2; i >= 0; --i) {
        /// speed_B = n-i-1 ///
        tB[i] = tB[i+1] + (fl[i+1] - fl[i]) / (n-i-1);
    }
    
    // cout << "tA : "; for (auto x : tA) cout << x << " "; cout << "\n";
    // cout << "tB : "; for (auto x : tB) cout << x << " "; cout << "\n";
    
    for (int i = 0; i <= n-1; ++i) {
        if (abs(tA[i] - tB[i]) <= eps) {
            cout << fixed << setprecision(9) << tA[i] << "\n";
            return;
        }
    }
    
    for (int i = 0; i <= n-2; ++i) {
        if (tA[i] <= tB[i] and tA[i+1] >= tB[i+1]) {
            double dis = fl[i+1] - fl[i];
            double spA = i+1;
            double spB = n-i-1;
            double ans = max(tA[i], tB[i+1]);
            // cout << "spA = " << spA << "\n";
            // cout << "spB = " << spB << "\n";
            if (tB[i+1] > tA[i]) dis -= (tB[i+1] - tA[i]) * spA;
            else                 dis -= (tA[i] - tB[i+1]) * spB;
            ans += dis / (spA + spB);
            cout << fixed << setprecision(9) << ans << "\n";
            return;
        }
    }
}

int32_t main() {
    fastIO();
    
    int t = 1;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
