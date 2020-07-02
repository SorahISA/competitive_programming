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
    
    int n;
    cin >> n;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    sort(ALL(v));
    
    deque<int> straw;
    for (auto x : v) {
        if (straw.size() < 2) {straw.push_front(x); continue;}
        if (straw[0] == x and straw[1] == x) straw.pop_front(), straw.pop_front();
        else straw.push_front(x);
    }
    
    int two_cnt = 0, deq_sz = straw.size();
    for (int i = 0; i+1 < deq_sz; ++i) {
        if (straw[i] == straw[i+1]) ++two_cnt;
    }
    
    cout << (2 * deq_sz - 1) / 3 - min(two_cnt, (deq_sz + 1) / 3) << "\n";
    
    return 0;
}
