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

bool isL(char x) {
    return x == '(' or x == '[' or x == '{';
}

int32_t main() {
    fastIO();
    
    string s;
    cin >> s;
    
    map<char, int> mp{{'(', 0}, {')', 1},
                      {'[', 2}, {']', 3},
                      {'{', 4}, {'}', 5}};
    
    stack<char> stk;
    for (auto x : s) {
        if (isL(x)) stk.push(x);
        else {
            if (stk.empty() or (mp[stk.top()] ^ mp[x]) != 1) return cout << "ERROR\n", 0;
            stk.pop();
        }
    }
    
    if (stk.empty()) cout << s.size() / 2 << "\n";
    else cout << "ERROR\n";
    
    return 0;
}
