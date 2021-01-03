// #pragma GCC target("avx2")
#pragma GCC optimize("Ofast", "unroll-loops")

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
const int maxn = 15000 + 5;

vector<int> v(maxn);
vector<pii> qry;
map<pii, int> func;
int tok = 0;

void call(int x, int y) {
    // cout << "call : " << x << " " << y << "\n";
    if (func[{v[x], v[y]}]) v[x] = v[y] = func[{v[x], v[y]}];
    else v[x] = v[y] = func[{v[x], v[y]}] = ++tok;
    qry.eb(x, y);
}

void solve() {
    iota(ALL(v), 0);
    
    int n;
    cin >> n;
    
    for (int s = 1; s < n; s <<= 1) {
        for (int i = 1; i+s+s-1 <= n; i += s<<1) {
            for (int j = 0; j < s and i+j+s <= n; ++j) call(i+j, i+j+s);
        }
    }
    
    deque<int> vec[16]; /// cnt = 2^i
    for (int i = n, j = 1, k = 0; i; i &= ~j, j <<= 1, ++k) {
        // if (i & j) cout << __lg(j) << " ";
        if (i & j) {
            for (int p = 0; p < j; ++p) vec[k].eb(i - p);
        }
    }
    
    int mx = __lg(n);
    for (int i = 0; i < mx; ++i) {
        if (vec[i].size() != vec[i+1].size()) {
            while (vec[i].size() > 0) {
                int tmpA = vec[i].front(); vec[i].pop_front();
                int tmpB = vec[mx].front(); vec[mx].pop_front();
                call(tmpA, tmpB);
                vec[i+1].eb(tmpA), vec[i+1].eb(tmpB);
            }
        }
        else {
            while (!vec[i].empty()) {
                vec[i+1].eb(vec[i].front());
                vec[i].pop_front();
            }
        }
        
        // cout << "sz : " << vec[i+1].size() << " <=> " << (1 << i+2) << "\n";
        if (vec[i+1].size() == (1 << i+2)) {
            for (int j = 0, k = (1<<i+2)-1; j < (1<<i+1); ++j, --k) {
                call(vec[i+1][j], vec[i+1][k]);
            }
        }
        
        /*
        for (int i = 0; i <= mx; ++i) {
            cout << "array " << i << " : ";
            for (auto x : vec[i]) cout << x << " ";
            cout << "\n";
        }
        
        cout << "query : " << qry.size() << "\n";
        cout << "result : ";
        if (n <= 128) for (int i = 1; i <= n; ++i) cout << v[i] << " \n"[i == n];
        else cout << "too long\n";
        cout << "\n";
        */
    }
    
    /*
    cout << "query : " << qry.size() << "\n";
    cout << "result : ";
    if (n <= 128) for (int i = 1; i <= n; ++i) cout << v[i] << " \n"[i == n];
    else cout << "too long\n";
    */
    
    /*
    set<int> checker;
    for (int i = 1; i <= n; ++i) checker.insert(v[i]);
    cout << "size : " << checker.size() << "\n";
    */
    
    /*
    while (1) {
        int a, b;
        cin >> a >> b;
        call(a, b);
        
        cout << "query : " << qry.size() << "\n";
        cout << "result : ";
        if (n <= 128) for (int i = 1; i <= n; ++i) cout << v[i] << " \n"[i == n];
        else cout << "too long\n";
    }
    */
    
    cout << qry.size() << "\n";
    for (auto [x, y] : qry) cout << x << " " << y << "\n";
}

int32_t main() {
    // fastIO();
    
    int t = 1;
    // cin >> t;
    while (t--) solve();
    
    return 0;
}
