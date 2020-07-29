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

const int INF = 0x7f7f7f7f;
const int mod = 1E9 + 7;
const int maxn = 1 << 17;

int BIT[maxn];

void Add(int idx) {
    while (idx < maxn) ++BIT[idx], idx += idx & -idx;
}

int Sum(int idx, int ans = 0) {
    while (idx) ans += BIT[idx], idx -= idx & -idx;
    return ans;
}

int32_t main() {
    fastIO();
    
    int n, cnt = 0;
    cin >> n;
    
    vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        string tmp;
        cin >> tmp;
        if (tmp == "X") vec[i] = INF, ++cnt;
        else            vec[i] = stoi(tmp);
    }
    
    if (n == 1) cout << "L\n";
    else if (cnt) cout << "LW"[cnt & 1] << "\n";
    else {
        vector<int> cp(vec);
        sort(ALL(cp));
        
        int ans = 0;
        for (auto &x : vec) {
            x = lower_bound(ALL(cp), x) - cp.begin() + 1;
            ans += Sum(n) - Sum(x), Add(x);
        }
        cout << "LW"[ans & 1] << "\n";
    }
    
    return 0;
}
