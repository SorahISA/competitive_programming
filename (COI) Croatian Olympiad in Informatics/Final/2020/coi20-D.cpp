// #pragma GCC target("avx2")
// #pragma GCC optimize("O3", "unroll-loops")

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
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

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
const int maxn = 2E5 + 5;

int Query(int L, int R, int res = 0) {
    cout << "? " << L+1 << " " << R+1 << endl;
    cin >> res;
    return res;
}

int32_t main() {
    fastIO();
    
    int n, q, res;
    cin >> n >> q;
    
    string s(n, '_');
    
    stack<int> left;
    for (int L = 0, R = 1; R < n; ++R) {
        res = Query(L, R);
        if (res == 0) {
            left.push(L), L = R;
        }
        if (res == 1) {
            s[L] = '(', s[R] = ')';
            if (left.empty()) L = ++R;
            else L = left.top(), left.pop();
        }
    }
    
    int blank = 0, _L = 0;
    for (auto c : s) blank += c == '_';
    _L = blank / 2;
    for (auto &c : s) {
        if (c != '_') continue;
        if (_L) --_L, c = ')';
        else          c = '(';
    }
    
    cout << "! " << s << "\n" << flush;
    
    return 0;
}
