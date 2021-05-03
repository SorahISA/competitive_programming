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
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % (uint64_t)(R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxn = 3E5 + 5;

int64_t cost;
int n, cnt = 0, new_cnt;
vector<int64_t> val;
vector<int> p, vis, v;
vector<pii> adj[maxn], adjtmp[maxn], edge, to_update;
map<pii, int> edgeID;

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}

int U(int x, int y) {
    x = R(x), y = R(y);
    if (x == y) return 0;
    if (adj[x].size() > adj[y].size()) swap(x, y);
    p[x] = y, val[y] += val[x] - cost;
    // to_update.eb(x, y);
    return 1;
}

void UpdateADJ() {
    /*
    for (auto [x, y] : to_update) {
        for (auto [fr, to] : adj[x]) {
            if (R(to) != y) adj[y].eb(fr, to);
        }
        vector<pii>().swap(adj[x]);
        // adj[x].clear();
    }
    vector<pii>().swap(to_update);
    // to_update.clear();
    */
    for (int i = 0; i < n; ++i) {
        for (auto [fr, to] : adj[i]) {
            int _fr = R(fr), _to = R(to);
            if (_fr != _to) adjtmp[_fr].eb(fr, to);
        }
    }
    for (int i = 0; i < n; ++i) {
        adjtmp[i].swap(adj[i]);
        vector<pii>().swap(adjtmp[i]);
    }
}

void dfs(int now) {
    vis[now] = 1;
    // cout << "\nnow: " << now << "\n";
    for (auto [fr, to] : adj[now]) {
        int _to = R(to), _now = R(now);
        // cout << "(now, R(now), to, R(to)): "
             // << now << " " << _now << " " << to << " " << _to << "\n";
        // cout << "val: " << val[_now] << " " << val[_to] << "\n";
        if (vis[_to] or _now == _to) continue;
        if (val[_now] + val[_to] >= cost) {
            edge.eb(fr+1, to+1);
            int tmp = U(_now, _to);
            // assert(tmp);
            new_cnt += tmp, dfs(_to);
        }
    }
}

void solve() {
    int m; cin >> n >> m >> cost;
    p.resize(n), iota(ALL(p), 0);
    val.resize(n), vis.resize(n);
    
    for (auto &x : val) cin >> x;
    
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y;
        if (x > y) swap(x, y);
        edgeID[{x, y}] = i+1;
        --x, --y, adj[x].eb(x, y), adj[y].eb(y, x);
    }
    
    if (accumulate(ALL(val), (int64_t)0) < (n - 1) * cost) return cout << "NO\n", void();
    
    while (cnt < n-1) {
        new_cnt = 0;
        v.clear();
        for (int i = 0; i < n; ++i) v.eb(R(i));
        sort(ALL(v), [](auto x, auto y) {
            return val[x] ^ val[y] ? val[x] > val[y] : x < y;
        });
        v.resize(unique(ALL(v)) - begin(v));
        // assert((int)v.size() == n - cnt);
        
        // cout << "v: " << v << "\n";
        
        fill(ALL(vis), 0);
        for (auto x : v) if (!vis[x]) dfs(x);
        UpdateADJ(), cnt += new_cnt;
        
        // cout << "new_cnt: " << new_cnt << "\n";
        
        if (new_cnt == 0) return cout << "NO\n", void();
    }
    
    cout << "YES\n";
    for (auto [x, y] : edge) {
        if (x > y) swap(x, y);
        cout << edgeID[{x, y}] << "\n";
    }
    
    // cout << edge << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}