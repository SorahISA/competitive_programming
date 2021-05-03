#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
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
        if (i) os << "\n";
        os << vec[i];
    }
    return os;
}

const int maxn = 3E5 + 5;

int cost;
vector<int> val, p, print_later;
vector<pii> adj[maxn]; /// (to, edgeID)

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
int U(int x, int y) {x = R(x), y = R(y); return x ^ y ? p[x] = y, 1 : 0;}

void dfs(int now, int lst = -1) {
    int parEdgeID = -1;
    for (auto [to, edgeID] : adj[now]) {
        if (to == lst) parEdgeID = edgeID;
        else dfs(to, now);
    }
    if (lst == -1) return;
    if (val[now] >= cost) {
        val[lst] += val[now] - cost;
        cout << parEdgeID << "\n";
    }
    else {
        print_later.eb(parEdgeID);
    }
}

void solve() {
    int n, m; cin >> n >> m >> cost;
    p.resize(n), iota(ALL(p), 0);
    val.resize(n);
    
    for (auto &x : val) cin >> x;
    
    vector<pii> edge(m);
    for (auto &[x, y] : edge) cin >> x >> y, --x, --y;
    
    if (accumulate(ALL(val), (int)0) < (n-1) * cost) return cout << "NO\n", void();
    else cout << "YES\n";
    
    for (int i = 0; i < m; ++i) {
        auto [u, v] = edge[i];
        if (U(u, v)) adj[u].eb(v, i+1), adj[v].eb(u, i+1);
    }
    
    dfs(0), reverse(ALL(print_later));
    cout << print_later << "\n";
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