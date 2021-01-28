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

const int maxn = 1E5 + 5;

int32_t main() {
    fastIO();
    
    int n, sum = 0;
    cin >> n;
    
    vector<pii> v(n);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        
        int cnt = 0;
        for (auto c : s) {
            if (c == 's') ++cnt;
            if (c == 'h') sum += cnt;
        }
        
        v[i].X = cnt, v[i].Y = s.size() - cnt;
    }
    
    sort(ALL(v), [](auto p1, auto p2) {
        return p1.X * p2.Y > p1.Y * p2.X;
    });
    
    int cnt = 0;
    for (auto [s, h] : v) {
        sum += cnt * h;
        cnt += s;
    }
    
    cout << sum << "\n";
    
    return 0;
}
