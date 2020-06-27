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

vector<int> J, O, I;

int32_t main() {
    fastIO();
    
    int n, k;
    string s;
    cin >> n >> k >> s;
    
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'J') J.eb(i);
        if (s[i] == 'O') O.eb(i);
        if (s[i] == 'I') I.eb(i);
    }
    
    int Jz = J.size(), Oz = O.size(), Iz = I.size();
    // if (Jz < k or Oz < k or Iz < k) return cout << -1 << "\n", 0;
    
    // int pL = J[k - 1], pR = I[Iz - k];
    // int cnt = lower_bound(ALL(O), pR) - lower_bound(ALL(O), pL);
    // if (cnt < k) return cout << -1 << "\n", 0;
    
    int minCost = INF;
    for (int L = 0, R = k-1; R < Jz; ++L, ++R) {
        int O_ends = lower_bound(ALL(O), J[R]) - O.begin() + k - 1;
        if (O_ends >= Oz) continue;
        int I_ends = lower_bound(ALL(I), O[O_ends]) - I.begin() + k - 1;
        if (I_ends >= Iz) continue;
        minCost = min(minCost, (I[I_ends] - J[L] + 1) - 3 * k);
    }
    
    cout << (minCost == INF ? -1 : minCost) << "\n";
    
    return 0;
}
