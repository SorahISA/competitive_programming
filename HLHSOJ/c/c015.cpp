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
    
    int n, m, k, num;
    vector<int> v;
    string s;
    stringstream ss;
    
    /// processing input ///
    cin >> n, getline(cin, s);
    
    getline(cin, s), ss << s;
    while (ss >> num) v.eb(num);
    m = v.size();
    
    cin >> k;
    /// till here ///
    
    int cnt = 0, ans = 0;
    bitset<25> books;
    for (int i = 0; i < m; ++i) {
        if (books[v[i]]) continue;
        
        if (cnt < k) ++cnt, books[v[i]] = 1;
        else {
            int latest_place = i, latest_num = -1;
            for (int j = 1; j <= n; ++j) {
                if (books[j]) {
                    for (int pl = i+1; pl < m; ++pl) {
                        if (v[pl] == j) {
                            if (pl > latest_place) latest_place = pl, latest_num = j;
                            break;
                        }
                        if (pl == m-1) latest_place = m-1, latest_num = j;
                    }
                }
            }
            
            ++ans;
            books[latest_num] = 0;
            books[v[i]] = 1;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
