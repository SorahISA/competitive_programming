// #pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

// #define int long long
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

#define ls(x) ((x) << 1)
#define rs(x) ((x) << 1 | 1)

struct Event {
    int u, v, sv;
    /// merge (u, v) ///
};

const int INF = 0x7f7f7f7f;
const int mod = 1E9 + 7;
const int maxn = 1 << 19;

int cc_cnt;
int par[maxn], sz[maxn];
stack<Event> stk;
vector<pii> event[maxn << 1];

int Root(int x) {
    while (x ^ par[x]) x = par[x];
    return x;
}

void Union(int x, int y) {
    x = Root(x), y = Root(y);
    // if (x == y) {stk.push({-1, -1, -1}); return;}
    if (sz[x] > sz[y]) swap(x, y);
    
    stk.push({x, y, sz[y]}), --cc_cnt;
    par[x] = y, sz[y] += sz[x];
}

void Undo() {
    Event ev = stk.top(); stk.pop();
    // if (ev.u == -1) return;
    
    par[ev.u] = ev.u, ++cc_cnt;
    sz[ev.v] = ev.sv;
}

void AddEvent(int qL, int qR, pii ev, int id = 1, int nL = 0, int nR = maxn-1) {
    if (qL <= nL and nR <= qR) {event[id].eb(ev); return;}
    // if (qR < nL or nR < qL) return;
    
    int mi = nL + nR >> 1;
    if (qL <= mi) AddEvent(qL, qR, ev, ls(id), nL,     mi);
    if (qR >  mi) AddEvent(qL, qR, ev, rs(id), mi + 1, nR);
}

void Traversal(int q, int id = 1, int nL = 0, int nR = maxn-1) {
    if (nL > q) return;
    
    int cnt = 0;
    for (auto ev : event[id]) {
        if (Root(ev.X) != Root(ev.Y)) Union(ev.X, ev.Y), ++cnt;
    }
    
    if (nL == nR) {
        if (nL != 0) cout << cc_cnt << "\n";
    }
    else {
        int mi = nL + nR >> 1;
        Traversal(q, ls(id), nL,     mi);
        Traversal(q, rs(id), mi + 1, nR);
    }
    
    while (cnt--) Undo();
    event[id].clear();
}

void solve() {
    int n, m, q, ai, bi;
    char c;
    cin >> n >> m >> q, cc_cnt = n;
    iota(par, par + n, 0);
    fill( sz,  sz + n, 1);
    
    map<pii, pii> con;
    for (int i = 0; i < m; ++i) {
        cin >> ai >> bi;
        if (ai > bi) swap(ai, bi);
        ++con[{ai, bi}].Y;
    }
    for (int i = 1; i <= q; ++i) {
        cin >> c >> ai >> bi;
        if (ai > bi) swap(ai, bi);
        
        if (c == 'N') {
            if (con[{ai, bi}].Y == 0) con[{ai, bi}] = {i, 1};
            else ++con[{ai, bi}].Y;
        }
        if (c == 'D') {
            if (con[{ai, bi}].Y == 1) {
                AddEvent(con[{ai, bi}].X, i - 1, {ai, bi});
                con.erase({ai, bi});
            }
            else --con[{ai, bi}].Y;
        }
    }
    
    for (auto ev : con) {
        if (ev.Y.Y >= 1) AddEvent(ev.Y.X, q, ev.X);
    }
    con.clear();
    
    Traversal(q);
}

int32_t main() {
    fastIO();
    
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
