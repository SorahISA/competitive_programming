#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define ef push_front
#define pf pop_front
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template <typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int MAXN = 1e5+5, MAXlg = __lg(MAXN)+2;
const int INF = 0x3f3f3f3f;
vector<int> tree[MAXN], e[MAXN], sp;
int dsu[MAXN],sz[MAXN],dep[MAXN];
int anc[MAXN][MAXlg];

map<int,int> dis[MAXN];

int fnd(int x){
    if (dsu[x] == x) return x;
    return dsu[x] = fnd(dsu[x]);
}
bool mrg(int x,int y){
    x = fnd(x), y = fnd(y);
    if (x == y) return false;
    if (sz[x] < sz[y]) swap(x, y);
    dsu[y] = x;
    sz[x] += sz[y];
    return true;
}
void BFS(int x){
    vector<int> tpdis(MAXN, INF);
    tpdis[x] = 0;
    queue<int> q;
    q.emplace(x);
    while (SZ(q)) {
        int cur = q.front();
        q.pop();
        for (auto i : e[cur]) {
            if (tpdis[i] > tpdis[cur] + 1) {
                tpdis[i] = tpdis[cur] + 1;
                q.emplace(i);
            }
        }
    }
    for (auto v : sp) {
        dis[x][v] = tpdis[v];
    }
}
void dfs(int x,int p,int d) {
    anc[x][0] = p;
    dep[x] = d;
    for (int i=1;1<<i < MAXN;++i) {
        anc[x][i] = anc[anc[x][i-1]][i-1];
    }
    for (auto i : tree[x]) {
        if (i == p) continue;
        dfs(i, x, d+1);
    }
}
int LCA(int x,int y) {
    int ret = 0;
    // cerr << "SSSS: " << x << ' ' << y << '\n';
    if (dep[x] < dep[y]) swap(x, y);
    for (int i=MAXlg-1;i>=0;--i) {
        if (((dep[x] - dep[y]) >> i) & 1) {
            x = anc[x][i];
            ret += (1LL<<i);
        }
    }
    // cerr << "BBBB: " << x << ' ' << y << '\n';
    if (x == y) return ret;
    for (int i=MAXlg-1;i>=0;--i) {
        if (anc[x][i] != anc[y][i]) {
            x = anc[x][i];
            y = anc[y][i];
            ret += (1LL<<i) * 2LL;
        }
    }
    // cerr << "AAAA: " << x << ' ' << y << '\n';
    assert(anc[x][0] == anc[y][0]);
    // cerr << "ANC: " << anc[x][0] << '\n';
    return ret + 2;
}
void solve() {
    int n,m;
    cin >> n >> m;
    for (int i=0;i<n;++i) {
        dsu[i] = i, sz[i] = 1;
    }
    for (int i=0;i<m;++i){
        int u,v;
        cin >> u >> v;
        u--, v--;
        e[u].emplace_back(v);
        e[v].emplace_back(u);
        if (mrg(u, v)) {
            tree[u].emplace_back(v);
            tree[v].emplace_back(u);
        }
        else {
            sp.emplace_back(u);
            sp.emplace_back(v);
        }
    }
    sort(ALL(sp));
    sp.resize(unique(ALL(sp)) - sp.begin());
    for (int i=0;i<SZ(sp);++i) {
        // cerr << "SP: " << sp[i] << '\n';
        BFS(sp[i]);
    }
    dfs(0, 0, 0);
    int q;
    cin >> q;
    while (q--) {
        int u,v;
        cin >> u >> v;
        u--, v--;
        int ans = LCA(u, v);
        for (auto v1 : sp) {
            for (auto v2 : sp) {
                ans = min(ans, dis[v1][v2] + LCA(u, v1) + LCA(v2, v));
            }
        }
        cout << ans << '\n';
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
