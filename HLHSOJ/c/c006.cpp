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
const double eps = 1e-6;

int32_t main() {
    fastIO();
    
    char a, b, c;
    cin >> a >> b >> c;
    if (a > b) swap(a, b);
    
         if (a == 'A' and b == 'B') cout << "C D\n";
    else if (a == 'A' and b == 'C') cout << "B D\n";
    else if (a == 'A' and b == 'D') cout << "B C\n";
    else if (a == 'A' and b == 'E') cout << "D\n";
    else if (a == 'A' and b == 'G') cout << "C D\n";
    else if (a == 'A' and b == 'H') cout << "D\n";
    else if (a == 'A' and b == 'J') cout << "D\n";
    else if (a == 'B' and b == 'C') cout << "A D\n";
    else if (a == 'B' and b == 'D') cout << "A C\n";
    else if (a == 'B' and b == 'E') cout << "D\n";
    else if (a == 'B' and b == 'G') cout << "C D\n";
    else if (a == 'B' and b == 'H') cout << "D\n";
    else if (a == 'B' and b == 'J') cout << "D\n";
    else if (a == 'C' and b == 'D') cout << "A B G\n";
    else if (a == 'C' and b == 'E') cout << "D G\n";
    else if (a == 'C' and b == 'G') cout << "D\n";
    else if (a == 'C' and b == 'H') cout << "D\n";
    else if (a == 'C' and b == 'I') cout << "G\n";
    else if (a == 'C' and b == 'J') cout << "D G\n";
    else if (a == 'D' and b == 'E') cout << "G\n";
    else if (a == 'D' and b == 'F') cout << "E\n";
    else if (a == 'D' and b == 'G') cout << "J\n";
    else if (a == 'D' and b == 'I') cout << "G J\n";
    else if (a == 'D' and b == 'J') cout << "G\n";
    else if (a == 'E' and b == 'G') cout << "D\n";
    else if (a == 'E' and b == 'H') cout << "D\n";
    else if (a == 'E' and b == 'I') cout << "G\n";
    else if (a == 'E' and b == 'J') cout << "D G\n";
    else if (a == 'F' and b == 'G') cout << "E\n";
    else if (a == 'G' and b == 'H') cout << "D\n";
    else if (a == 'G' and b == 'I') cout << "J\n";
    else if (a == 'G' and b == 'J') cout << "I\n";
    else if (a == 'H' and b == 'J') cout << "D\n";
    else if (a == 'I' and b == 'J') cout << "G\n";
    else cout << "0\n";
    
    if (c == 'A' or c == 'B' or c == 'C' or c == 'D') {
        cout << "A B C D 96\n";
    }
    else if (c == 'E') {
        cout << "D E G 18\n";
    }
    else if (c == 'F') {
        cout << "E F 2\n";
    }
    else if (c == 'G') {
        cout << "C D G 42\n";
    }
    else if (c == 'H') {
        cout << "D H 3\n";
    }
    else if (c == 'I' or c == 'J') {
        cout << "G I J 39\n";
    }
    
    return 0;
}
