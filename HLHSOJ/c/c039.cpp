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

string sss, ss, s1, s2, s3, ex1, ex2;
int prize[6] = {
    200'000,
     40'000,
     10'000,
      4'000,
      1'000,
        200,
};

int solve() {
    string str;
    cin >> str;

    if (str == sss) return 10'000'000;
    if (str ==  ss) return  2'000'000;

    for (int i = 0; i <= 5; ++i) {
        if (str.substr(i) == s1.substr(i)) return prize[i];
        if (str.substr(i) == s2.substr(i)) return prize[i];
        if (str.substr(i) == s3.substr(i)) return prize[i];
    }

    if (str.substr(5) == ex1) return 200;
    if (str.substr(5) == ex2) return 200;

    return 0;
}

int32_t main() {
    fastIO();
    
    cin >> sss >> ss >> s1 >> s2 >> s3 >> ex1 >> ex2;

    int t, tot = 0;
    cin >> t;
    while (t--) tot += solve();
    cout << tot << "\n";

    return 0;
}
