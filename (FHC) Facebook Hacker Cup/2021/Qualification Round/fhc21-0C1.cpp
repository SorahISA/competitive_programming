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
#define pf pop_front
#define pb pop_back
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

void chmax(int &x, int y) {x = max(x, y);}

const int maxn = 50 + 5;

vector<int> adj[maxn], val, max_path_val;

void dfs(int now, int lst) {
    for (auto x : adj[now]) {
        if (x == lst) continue;
        dfs(x, now);
        chmax(max_path_val[now], max_path_val[x]);
    }
    max_path_val[now] += val[now];
}

void solve() {
    int N; cin >> N;
    
    val.resize(N);
    for (auto &x : val) cin >> x;
    
    for (int i = 0; i < N-1; ++i) {
        int u, v; cin >> u >> v, --u, --v;
        adj[u].eb(v), adj[v].eb(u);
    }
    max_path_val.assign(N, 0), dfs(0, -1);
    
    if (adj[0].size() <= 1) cout << max_path_val[0] << "\n";
    else {
        sort(ALL(adj[0]), [](auto x, auto y) {
            return max_path_val[x] > max_path_val[y];
        });
        cout << max_path_val[adj[0][0]] + max_path_val[adj[0][1]] + val[0] << "\n";
    }
}

void init() {
    for (int i = 0; i < maxn; ++i) adj[i].clear();
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case #" << _ << ": ";
        init(), solve();
    }
    
    return 0;
}