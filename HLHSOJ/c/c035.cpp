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
const int maxn = 1001 + 5;

int arr[2][maxn][maxn], col[2][maxn], row[2][maxn], diag[2][2];
pii pl[2][maxn * maxn];

int32_t main() {
    fastIO();
    
    int n, p, l;
    cin >> n >> p >> l;
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> arr[0][i][j], pl[0][arr[0][i][j]] = {i, j};
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> arr[1][i][j], pl[1][arr[1][i][j]] = {i, j};
        }
    }
    
    int num, line1 = 0, line2 = 0;
    while (l--) {
        cin >> num;
        if (pl[0][num] != pii{0, 0}) {
            if (++col[0][pl[0][num].X] == n) ++line1;
            if (++row[0][pl[0][num].Y] == n) ++line1;
            if (pl[0][num].X == pl[0][num].Y and ++diag[0][0] == n) ++line1;
            if (pl[0][num].X + pl[0][num].Y == n + 1 and ++diag[0][1] == n) ++line1;
        }
        if (pl[1][num] != pii{0, 0}) {
            if (++col[1][pl[1][num].X] == n) ++line2;
            if (++row[1][pl[1][num].Y] == n) ++line2;
            if (pl[1][num].X == pl[1][num].Y and ++diag[1][0] == n) ++line2;
            if (pl[1][num].X + pl[1][num].Y == n + 1 and ++diag[1][1] == n) ++line2;
        }
        
        if (line1 >= p or line2 >= p) {
            cout << num << " " << line1 << " " << line2 << "\n";
        }
        if (line1 >= p and line2 >= p) {cout << "Draw\n"; break;}
        if (line1 >= p) {cout << "The winner is Baluteshih\n"; break;}
        if (line2 >= p) {cout << "The winner is Alan\n"; break;}
    }
    
    return 0;
}
