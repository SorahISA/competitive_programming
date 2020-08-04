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

int32_t main() {
    fastIO();
    
    int n;
    string s, str[] = {"vaporeon", "jolteon", "flareon", "espeon", "umbreon", "leafeon", "glaceon", "sylveon"};
    
    cin >> n >> s;
    for (int i = 0; i < 8; ++i) {
        if (str[i].size() == n) {
            int fl = 1;
            for (int j = 0; j < n; ++j) {
                if (s[j] == '.' or s[j] == str[i][j]);
                else fl = 0;
            }
            if (fl) return cout << str[i] << "\n", 0;
        }
    }

    return 0;
}