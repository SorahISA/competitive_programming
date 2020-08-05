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
                 uniform_int_distribution<int> __dis(1, 7); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E18;
const int mod = 1E9 + 7;

int32_t main() {
    fastIO();
    
    int a, b, c;
    cin >> a >> b >> c;
    
    int mn = min({a, b, c});
    cout << max({mn >= 0 ? mn   + (a-mn)  /3 + (b-mn)  /3 + (c-mn)  /3 : 0LL,
                 mn >= 1 ? mn-1 + (a-mn+1)/3 + (b-mn+1)/3 + (c-mn+1)/3 : 0LL,
                 mn >= 2 ? mn-2 + (a-mn+2)/3 + (b-mn+2)/3 + (c-mn+2)/3 : 0LL}) << "\n";
    
    return 0;
}
