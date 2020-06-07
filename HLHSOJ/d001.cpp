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

int sz, sp, ep, limL, limR, minAns = 36;
string s, t;

map<string, int> st;

void dfs(int lst, int dep) {
    // if (dep <= 15) cout << dep << " : " << s << "\n";
    if (s == t) {/*cout << "LOOK HERE !!! " << dep << "\n";*/ minAns = min(minAns, dep); return;}
    if (dep >= minAns) return;
    if (st[s] and st[s] <= dep) return;
    st[s] = dep;
    
    for (int dx : {-2, -1, 1, 2}) {
        if (dx == -lst) continue;
        if (sp + dx < limL or sp + dx > limR) continue;
        // if (sp + dx < 0 or sp + dx >= sz) continue;
        swap(s[sp], s[sp + dx]), sp += dx;
        pii rollback{limL, limR};
        for (; s[limL] == t[limL] and s[limL] != '0'; ++limL);
        for (; s[limR] == t[limR] and s[limR] != '0'; --limR);
        dfs(dx, dep + 1);
        limL = rollback.X, limR = rollback.Y;
        swap(s[sp], s[sp - dx]), sp -= dx;
    }
}

int32_t main() {
    fastIO();
    
    cin >> s >> t, sz = s.size();
    for (sp = 0; s[sp] != '0'; ++sp);
    for (ep = 0; t[ep] != '0'; ++ep);
    for (limL =    0; s[limL] == t[limL] and s[limL] != '0'; ++limL);
    for (limR = sz-1; s[limR] == t[limR] and s[limR] != '0'; --limR);
    
    dfs(0, 0);
    
    cout << minAns << "\n";
    
    return 0;
}
