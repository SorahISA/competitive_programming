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
    
    int n, k, a, b, c, d, score[2] = {0, 0}, streak[2] = {0, 0};
    string s, t;
    cin >> n >> k;
    cin >> a >> b >> c >> d;
    cin >> s >> t;
    
    for (int i = 0; i < n; ++i) {
        if (s[i] == t[i]) {
            streak[0] = streak[1] = 0;
            score[0] += b, score[1] += b;
        }
        else if ((s[i] == 'R' and t[i] == 'S') or
                 (s[i] == 'P' and t[i] == 'R') or
                 (s[i] == 'S' and t[i] == 'P')) {
            streak[0] = 0, ++streak[1];
            score[0] += a, score[1] += (streak[1] < k ? c : d);
        }
        else {
            ++streak[0], streak[1] = 0;
            score[0] += (streak[0] < k ? c : d), score[1] += a;
        }
    }
    
    cout << score[0] << " " << score[1] << "\n";
    
    return 0;
}
