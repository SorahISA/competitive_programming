#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

template<typename T>
bool chmin(T &lhs, T rhs) {return lhs <= rhs ? 0 : (lhs = rhs, 1);}

template<typename T>
bool chmax(T &lhs, T rhs) {return lhs >= rhs ? 0 : (lhs = rhs, 1);}

const int maxn = 8E5 + 5;

int N, same_side, ans;
vector<int> adj[maxn], sz;
vector<int> F, all_F, cnt_F;

void Add(int now, int no_go, int type) {
    for (auto x : adj[now]) {
        if (x != no_go) Add(x, no_go, type);
    }
    if (cnt_F[F[now]] == 0 or cnt_F[F[now]] == all_F[F[now]]) --same_side;
    cnt_F[F[now]] += type;
    if (cnt_F[F[now]] == 0 or cnt_F[F[now]] == all_F[F[now]]) ++same_side;
}

void dfs_sz(int now, int lst) {
    for (auto x : adj[now]) {
        if (x != lst) dfs_sz(x, now), sz[now] += sz[x];
    }
}

void dfs(int now, int take) {
    int heavy = sz[now] > 1 ? adj[now][0] : -1;
    
    for (auto x : adj[now]) {
        if (x != heavy) dfs(x, 0);
    }
    
    if (heavy != -1) dfs(heavy, 1);
    
    Add(now, heavy, 1);
    if (now != 0 and same_side == N) ++ans;
    if (!take) Add(now, -1, -1);
}

void solve() {
    vector<pii> edge(N-1);
    for (auto &[u, v] : edge) {
        cin >> u >> v, --u, --v;
        adj[u].eb(v), adj[v].eb(u);
    }
    for (auto &x : F) cin >> x, --x, ++all_F[x];
    
    dfs_sz(0, -1);
    
    for (int i = 0; i < N; ++i) adj[i].clear();
    for (auto [u, v] : edge) {
        if (sz[u] > sz[v]) adj[u].eb(v);
        else               adj[v].eb(u);
    }
    for (int i = 0; i < N; ++i) {
        sort(ALL(adj[i]), [](auto x, auto y) {return sz[x] > sz[y];});
    }
    
    dfs(0, 0);
    
    cout << ans << "\n";
}

void init() {
    cin >> N;
    same_side = N;
    ans = 0;
    for (int i = 0; i < N; ++i) adj[i].clear();
    sz.assign(N, 1);
    F.resize(N);
    all_F.assign(N, 0);
    cnt_F.assign(N, 0);
    solve();
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case #" << _ << ": ";
        init();
    }
    
    return 0;
}
