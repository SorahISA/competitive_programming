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
                 uniform_int_distribution<int> __dis(0, 1); \
                 auto rnd = bind(__dis, __gen);

const int INF = 1E18;
const int mod = 1E9 + 7;

int32_t main() {
    // fastIO();
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<double>> v(n+5, vector<double>(m+5, 1e18));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> v[i][j];
    }
    
    int nowX = 0, nowY = 2, dir = 1; // dir = {1, 2, 3} : {left, up, down}
    for (int i = 1; i <= n; ++i) {
        if (v[i][1] < v[nowX][1]) nowX = i;
    }
    
    double sum = v[nowX][1] + (m >= 2 ? v[nowX][2] : 0.0);
    while (nowY != m) {
        if (dir == 1) {
            if (v[nowX][nowY+1] < min(v[nowX-1][nowY], v[nowX+1][nowY])) {
                sum += v[nowX][++nowY], dir = 1;
            }
            else if (v[nowX+1][nowY] < min(v[nowX-1][nowY], v[nowX][nowY+1])) {
                sum += v[++nowX][nowY], dir = 2;
            }
            else if (v[nowX-1][nowY] < min(v[nowX+1][nowY], v[nowX][nowY+1])) {
                sum += v[--nowX][nowY], dir = 3;
            }
        }
        else if (dir == 2) {
            if (v[nowX][nowY+1] < v[nowX+1][nowY]) {
                sum += v[nowX][++nowY], dir = 1;
            }
            else if (v[nowX+1][nowY] < v[nowX][nowY+1]) {
                sum += v[++nowX][nowY], dir = 2;
            }
        }
        else if (dir == 3) {
            if (v[nowX][nowY+1] < v[nowX-1][nowY]) {
                sum += v[nowX][++nowY], dir = 1;
            }
            else if (v[nowX-1][nowY] < v[nowX][nowY+1]) {
                sum += v[--nowX][nowY], dir = 3;
            }
        }
    }
    
    cout << fixed << setprecision(6) << sum << "\n";
    
    return 0;
}
