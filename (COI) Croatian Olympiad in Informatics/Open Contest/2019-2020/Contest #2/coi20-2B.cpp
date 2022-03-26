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
    
    int n, type, val;
    cin >> n;
    
    vector<int> v[9];
    for (int i = 1; i <= 8; ++i) v[i].eb(0);
    for (int i = 0; i < n; ++i) {
        cin >> type >> val, v[type].eb(val);
    }
    for (int i = 1; i <= 8; ++i) sort(ALL(v[i]));
    
    if (v[5].size() == 2 and v[7].size() == 2) {
        if (v[4].size() != v[1].size() + 1) {
            return cout << -1 << "\n", 0;
        }
    }
    else if (v[6].size() == 2 and v[8].size() == 2) {
        if (v[1].size() != v[4].size() + 1) {
            return cout << -1 << "\n", 0;
        }
    }
    else {
        if (v[1].size() != v[4].size()) {
            return cout << -1 << "\n", 0;
        }
    }
    
    vector<pii> ans;
    if (v[5].size() == 2) {
        ans.eb(v[5][++v[5][0]], 5);
        while (1) {
            if (++v[4][0] == v[4].size()) break;
            ans.eb(v[4][v[4][0]], 4);
            if (++v[1][0] == v[1].size()) break;
            ans.eb(v[1][v[1][0]], 1);
        }
    }
    if (v[6].size() == 2) {
        ans.eb(v[6][++v[6][0]], 6);
        while (1) {
            if (++v[1][0] == v[1].size()) break;
            ans.eb(v[1][v[1][0]], 1);
            if (++v[4][0] == v[4].size()) break;
            ans.eb(v[4][v[4][0]], 4);
        }
    }
    if (v[7].size() == 2) ans.eb(v[7][++v[7][0]], 7);
    if (v[8].size() == 2) ans.eb(v[8][++v[8][0]], 8);
    
    int fl1 = 1, fl2 = 1;
    for (int i = ans.size()-1; i >= 0; --i) {
        if (fl1 and (ans[i].Y == 1 or ans[i].Y == 7)) fl1 = 0, ans[i].Y = 7;
        if (fl2 and (ans[i].Y == 4 or ans[i].Y == 8)) fl2 = 0, ans[i].Y = 8;
    }
    
    v[2].eb(INF), v[3].eb(INF);
    for (auto [Val, Type] : ans) {
        while (Type == 1 and v[2][v[2][0]+1] <  Val) cout << v[2][++v[2][0]] << " ";
        while (Type == 7 and v[2][v[2][0]+1] != INF) cout << v[2][++v[2][0]] << " ";
        while (Type == 4 and v[3][v[3][0]+1] <  Val) cout << v[3][++v[3][0]] << " ";
        while (Type == 8 and v[3][v[3][0]+1] != INF) cout << v[3][++v[3][0]] << " ";
        cout << Val << " ";
    }
    cout << "\n";
    
    return 0;
}
