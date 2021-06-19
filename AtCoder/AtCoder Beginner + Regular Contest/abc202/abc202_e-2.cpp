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
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxn = 2E5 + 5;

vector<int> adj[maxn], dep(maxn);
vector<pii> timestamp(maxn);
vector<int> st[maxn]; /// record timestamp in st[depth]

void dfs(int now) {
    static int tok = 0;
    st[dep[now]].eb(timestamp[now].X = ++tok);
    for (auto x : adj[now]) dfs(x);
    timestamp[now].Y = ++tok;
}

void solve() {
    int N; cin >> N;
    for (int i = 2, par; i <= N; ++i) cin >> par, adj[par].eb(i), dep[i] = dep[par] + 1;
    
    dfs(1);
    
    int Q; cin >> Q;
    while (Q--) {
        int u, d; cin >> u >> d;
        /// query how many x \in st[d] \cap [in_u, out_u] ///
        cout << upper_bound(ALL(st[d]), timestamp[u].Y)
              - lower_bound(ALL(st[d]), timestamp[u].X) << "\n";
    }
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