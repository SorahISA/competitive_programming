// #pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

#include <bits/extc++.h>
using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
template <typename T>
using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using pii = pair<int, int>;
// template<typename T>
// using prior = priority_queue<T, vector<T>, greater<T>>;
// template<typename T>
// using Prior = priority_queue<T>;

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
    
    int q, op, val, given = 0;
    deque<int> arr;
    pbds_set<pii> st;
    cin >> q;
    
    for (int _ = 1; _ <= q; ++_) {
        cin >> op >> val;
        if (op == 1) {
            arr.push_back(val + given);
            st.insert({val + given, _});
        }
        if (op == 2) {
            given += val;
            while (!arr.empty() and arr.front() <= given) {
                st.erase(st.lower_bound({arr.front(), 0}));
                arr.pop_front();
            }
            // cout << given << " : ";
            // for (auto x : st) cout << x.X << " ";
            cout << st.order_of_key({given, INF}) << "\n";
        }
    }
    
    return 0;
}
