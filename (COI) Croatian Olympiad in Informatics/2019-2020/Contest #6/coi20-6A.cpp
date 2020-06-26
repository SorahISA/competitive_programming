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

vector<pii> palin; /// (year , month+date)

void solve() {
    int d, m, y;
    scanf("%lld.%lld.%lld.", &d, &m, &y);
    
    auto ans = lower_bound(ALL(palin), pii{y, 0LL});
    if ((*ans).X > y or (*ans).Y%100 > m or ((*ans).Y%100 == m and (*ans).Y/100 > d)) {
        printf("%02lld.%02lld.%04lld.\n", (*ans).Y/100, (*ans).Y%100, (*ans).X);
    }
    else {
        ans = next(ans);
        printf("%02lld.%02lld.%04lld.\n", (*ans).Y/100, (*ans).Y%100, (*ans).X);
    }
}

void init() {
    palin.eb(2092, 2902);
    int days[] = {-1, 31, 28, 31, 30, 31, 30,
                      31, 31, 30, 31, 30, 31};
    
    for (int i = 1; i <= 12; ++i) {
        for (int j = 1; j <= days[i]; ++j) {
            palin.eb(j/10 + j%10*10 + i/10*100 + i%10*1000, j*100 + i);
        }
    }
    
    sort(ALL(palin));
}

int32_t main() {
    // fastIO();
    init();
    
    int t;
    scanf("%lld", &t);
    while (t--) solve();
    
    return 0;
}
