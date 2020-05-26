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
    
    int n, m, r, c;
    cin >> n >> m >> r >> c;
    
    int arr[n][m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> arr[i][j];
    }
    
    vector<int> ans;
    
    int rowAns[n][m];
    for (int i = 0; i < n; ++i) {
        deque<int> deq, idx;
        for (int j = 0; j < m; ++j) {
            while (!deq.empty() and arr[i][j] > deq.back()) deq.pop_back(), idx.pop_back();
            deq.push_back(arr[i][j]), idx.push_back(j);
            if (idx.front() == j - c) deq.pop_front(), idx.pop_front();
            rowAns[i][j] = deq.front();
        }
    }
    
#ifdef local
    cout << "rowAns with (n , m) = (" << n << " , " << m << ") :\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cout << rowAns[i][j] << " \n"[j == m-1];
    }
    cout << "\n";
#endif

    int colAns[n][m];
    for (int j = 0; j < m; ++j) {
        deque<int> deq, idx;
        for (int i = 0; i < n; ++i) {
            while (!deq.empty() and rowAns[i][j] > deq.back()) deq.pop_back(), idx.pop_back();
            deq.push_back(rowAns[i][j]), idx.push_back(i);
            if (idx.front() == i - r) deq.pop_front(), idx.pop_front();
            colAns[i][j] = deq.front();
        }
    }
    
#ifdef local
    cout << "colAns with (n , m) = (" << n << " , " << m << ") :\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cout << colAns[i][j] << " \n"[j == m-1];
    }
    cout << "\n";
#endif
    
    for (int i = r-1; i < n; ++i) {
        for (int j = c-1; j < m; ++j) ans.eb(colAns[i][j]);
    }
    sort(ALL(ans));
    
    for (auto x : ans) cout << x << " ";
    cout << "\n";
    
    return 0;
}
