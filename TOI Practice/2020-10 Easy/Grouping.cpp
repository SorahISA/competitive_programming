// #pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

// #define int long long
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

const int INF = 1E9;
const int mod = 1E9 + 7;
const int maxn = 10000 + 50;

int32_t main() {
    fastIO();
    
    int n, sz;
    string s;
    cin >> n >> s, sz = s.size();
    reverse(ALL(s));
    
    int maxStr = 0, maxId = 0;
    for (int i = 0; i < sz; i += n) {
        int str = 0;
        for (int j = i; j < min(i+n, sz); ++j) str += s[j] - '0';
        if (str >= maxStr) maxStr = str, maxId = i/n + 1;
    }
    
    cout << maxId << " " << maxStr << "\n";
    
    return 0;
}
