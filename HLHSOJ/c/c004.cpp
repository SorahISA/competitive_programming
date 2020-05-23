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
    fastIO();
    
    int n, tmp, fl = 1;
    char c;
    cin >> c >> n;
    
    int field[n][4][4];
    char name[n];
    for (int i = 0; i < n; ++i) {
        cin >> name[i];
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) cin >> field[i][j][k];
        }
    }
    
    cin >> c;
    for (int num = 1; num <= 16; ++num) {
        cin >> tmp;
        if (!fl) continue;
        cout << tmp << " ";
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 4; ++j) {
                for (int k = 0; k < 4; ++k) {
                    field[i][j][k] = field[i][j][k] ^ tmp ? field[i][j][k] : 0;
                }
            }
            
            bool check = 1;
            for (int j = 0; j < 4; ++j) {
                if (check and field[i][j][0] + field[i][j][1] + field[i][j][2] + field[i][j][3] == 0) {
                    check = fl = 0, cout << name[i] << " ";
                }
                if (check and field[i][0][j] + field[i][1][j] + field[i][2][j] + field[i][3][j] == 0) {
                    check = fl = 0, cout << name[i] << " ";
                }
            }
            if (check and field[i][0][0] + field[i][1][1] + field[i][2][2] + field[i][3][3] == 0) {
                check = fl = 0, cout << name[i] << " ";
            }
            if (check and field[i][0][3] + field[i][1][2] + field[i][2][1] + field[i][3][0] == 0) {
                check = fl = 0, cout << name[i] << " ";
            }
        }
    }
    cout << "\n";
    
    return 0;
}
