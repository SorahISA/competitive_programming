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
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1LL << 60;
const int maxc = 2E5 + 5;

int32_t main() {
    fastIO();
    
    int n, tmp;
    cin >> n;
    
    vector<int> cnt(maxc, 0);
    for (int i = 0; i < n; ++i) cin >> tmp, ++cnt[tmp];
    
    int maxans = 0, maxlp = 0, maxrp = 0, sum = 0;
    for (int lP = 1, rP = 1; rP <= maxc; ++rP) {
        if (cnt[rP] == 0) {lP = rP + 1, sum = 0; continue;}
        
        sum += cnt[rP];
        if (sum > maxans) maxans = sum, maxlp = lP, maxrp = rP;
        
        if (cnt[rP] == 1) lP = rP, sum = 1;
    }
    
    cout << maxans << "\n";
    for (int i = maxlp; i <= maxrp; ++i) {
        cout << i << " ";
        --cnt[i];
    }
    for (int i = maxrp; i >= maxlp; --i) {
        while (cnt[i]--) cout << i << " ";
    }
    cout << "\n";

    return 0;
}
