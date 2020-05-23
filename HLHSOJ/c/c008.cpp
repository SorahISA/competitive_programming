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
    // fastIO();
    
    int h1, m1, s1, h2, m2, s2;
    scanf("%lld:%lld:%lld", &h1, &m1, &s1);
    scanf("%lld:%lld:%lld", &h2, &m2, &s2);
    
    int sec1 = h1 * 3600 + m1 * 60 + s1;
    int sec2 = h2 * 3600 + m2 * 60 + s2;
    int sec3 = (sec2 - sec1 + 86400) % 86400;
    
    int h3 = sec3 / 3600, m3 = (sec3 / 60) % 60, s3 = sec3 % 60;
    printf("%02lld:%02lld:%02lld\n", h3, m3, s3);
    
    return 0;
}
