#include "shoes.h"

// #pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

#define int long long
// template <typename T>
// using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(0, 1); \
                 auto rnd = bind(__dis, __gen);

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 1 << 18;

vector<int> BIT(maxn, 0);

void Add(int idx) {while (idx < maxn) ++BIT[idx], idx += idx&-idx;}

int Sum(int idx, int ans = 0) {while (idx) ans += BIT[idx], idx -= idx&-idx; return ans;}

int count_swaps(vector<int32_t> _S) {
    vector<int> S;
    for (auto x : _S) S.eb(x);
    
    int n = S.size() / 2, ans = 0;
    map<int, int> trans;
    map<int, pii> place;
    vector<pii> pairs;
    set<int> appear;
    
    for (int i = 0, now = S[i]; i < 2*n; now = S[++i]) {
        if (!trans[now]) trans[now] = S[i];
        S[i] = trans[now];
        if (appear.count(S[i])) S[i] += (S[i] > 0 ? n : -n);
        appear.insert(S[i]), trans[now] = S[i];
    }
    
    // for (auto x : S) cout << x << ", ";
    
    appear.clear(), trans.clear();
    for (int i = 0; i < 2*n; ++i) {
        if (S[i] > 0 and !appear.count(-S[i])) ++ans;
        appear.insert(S[i]);
        S[i] = abs(S[i]);
    }
    
    for (int i = 0; i < 2*n; ++i) {
        if (place[S[i]].first) place[S[i]].second = i + 1;
        else place[S[i]].first = i + 1;
    }
    
    // for (auto x : place) cout << x.Y.X << ", " << x.Y.Y << "\n";
    for (auto x : place) pairs.eb(x.Y.X, x.Y.Y);
    sort(pairs.begin(), pairs.end());
    
    for (auto pl : pairs) {
        Add(pl.X), Add(pl.Y), ans += pl.Y - Sum(pl.Y);
    }
    
    return ans;
}
