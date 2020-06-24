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

int n;
vector<int> val, valA;
multiset<int> setB;

bool solve() {
    /*  Four types of solve() :
     *      A, A, A, ...
     *      A, A, B, ...
     *      A, B, A, ...
     *      B, A, A, ...
     */
    
    int diffA = valA[1] - valA[0];
    for (int i = 3; i < n; ++i) {
        if (val[i] - valA.back() == diffA) valA.eb(val[i]);
        else setB.insert(val[i]);
    }
    
    if (setB.empty()) {setB.insert(valA.back()), valA.pop_back(); return true;}
    if (setB.size() == 1) return true;
    
    int diffB = *next(setB.begin()) - *setB.begin();
    int lst = -1, cnt = 0;
    for (auto x : setB) {
        if (lst != -1 and x - lst != diffB) ++cnt;
        lst = x;
    }
    
    while (valA.size() >= 2 and cnt) {
        int ins = valA.back(); valA.pop_back();
        
        int diff1 = (setB.upper_bound(ins) == setB.end()) ?
                    diffB + 1 : *setB.upper_bound(ins) - ins;
        int diff2 = ins - *prev(setB.upper_bound(ins));
        
        if (min(diff1, diff2) < diffB) return false;
        if (diff1 == diffB and diff2 == diffB) --cnt;
        if (min(diff1, diff2) > diffB) ++cnt;
        
        setB.insert(ins);
    }
    
    return cnt == 0;
}

int32_t main() {
    fastIO();
    
    cin >> n;
    
    val.resize(n);
    for (auto &x : val) cin >> x;
    sort(ALL(val));
    
    if (n == 2) {
        cout << 1 << "\n" << val[0] << "\n";
        cout << 1 << "\n" << val[1] << "\n";
        return 0;
    }
    
    /// A, A, A, ... ///
    valA.clear(), setB.clear();
    valA.eb(val[0]), valA.eb(val[1]), valA.eb(val[2]);
    if (valA[1] - valA[0] == valA[2] - valA[1] and solve()) {
        cout << valA.size() << "\n";
        for (auto x : valA) cout << x << " ";
        cout << "\n";
        cout << setB.size() << "\n";
        for (auto x : setB) cout << x << " ";
        cout << "\n";
        return 0;
    }
    
    /// A, A, B, ... ///
    valA.clear(), setB.clear();
    valA.eb(val[0]), valA.eb(val[1]), setB.insert(val[2]);
    if (solve()) {
        cout << valA.size() << "\n";
        for (auto x : valA) cout << x << " ";
        cout << "\n";
        cout << setB.size() << "\n";
        for (auto x : setB) cout << x << " ";
        cout << "\n";
        return 0;
    }
    
    /// A, B, A, ... ///
    valA.clear(), setB.clear();
    valA.eb(val[0]), setB.insert(val[1]), valA.eb(val[2]);
    if (solve()) {
        cout << valA.size() << "\n";
        for (auto x : valA) cout << x << " ";
        cout << "\n";
        cout << setB.size() << "\n";
        for (auto x : setB) cout << x << " ";
        cout << "\n";
        return 0;
    }
    
    /// B, A, A, ... ///
    valA.clear(), setB.clear();
    setB.insert(val[0]), valA.eb(val[1]), valA.eb(val[2]);
    if (solve()) {
        cout << valA.size() << "\n";
        for (auto x : valA) cout << x << " ";
        cout << "\n";
        cout << setB.size() << "\n";
        for (auto x : setB) cout << x << " ";
        cout << "\n";
        return 0;
    }
    
    cout << -1 << "\n";
    
    return 0;
}
