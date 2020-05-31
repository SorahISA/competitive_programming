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
const int maxn = 1000 + 5;

vector<int> coeff(maxn, 0);

int32_t main() {
    fastIO();
    
    int n, q;
    string s;
    cin >> n >> q, getline(cin, s);
    getline(cin, s);
    for (auto &c : s) c = c == '+' ? ' ' : c;
    stringstream ss(s);
    
    int overall_mult = 1;
    while (ss >> s) {
        if (s == "-") {overall_mult = -1; continue;}
        
        int mult = overall_mult; overall_mult = 1; // +/-
        if (s[0] == '-') mult *= -1, s = s.substr(1);
        
        int num = 0, exp = 0, find_x = 0;
        
        if (s[0] == 'x') num = 1;
        for (auto c : s) {
            if (!find_x and isdigit(c)) num = num*10 + (c-'0');
            else find_x = 1;
            
            if ( find_x and isdigit(c)) exp = exp*10 + (c-'0');
        }
        if (find_x and !exp) exp = 1;
        
        coeff[exp] = (mult * num + mod) % mod;
        // cerr << "coeff[" << exp << "] " << mult * num << "\n";
    }
    
    while (q--) {
        int x, mult = 1, ans = 0;
        cin >> x, x = (x + mod) % mod;
        for (int i = 0; i <= n; ++i) {
            ans = (ans + mult * coeff[i]) % mod;
            mult = mult * x % mod;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
