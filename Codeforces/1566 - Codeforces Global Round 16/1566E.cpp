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

template<typename T>
bool chmin(T &lhs, T rhs) {return lhs <= rhs ? 0 : (lhs = rhs, 1);}

template<typename T>
bool chmax(T &lhs, T rhs) {return lhs >= rhs ? 0 : (lhs = rhs, 1);}

const int maxn = 2E5 + 5;

vector<int> adj[maxn], tp, budded; /// tp: 0 for leaf, 1 for bud

void dfs(int now, int lst) {
    int all_bud = 1, all_leaf_bud = 1;
    for (auto x : adj[now]) {
        if (x != lst) {
            dfs(x, now);
            all_bud &= tp[x] == 1;
            all_leaf_bud &= tp[x] == 0 or tp[x] == 1;
        }
    }
         if (all_bud)      tp[now] = 0;
    else if (all_leaf_bud) tp[now] = 1;
}

void dfs2(int now, int lst) {
    if (tp[now] == 1) budded[now] = 1;
    for (auto x : adj[now]) {
        if (x != lst) {
            budded[x] |= budded[now];
            dfs2(x, now);
        }
    }
}

void solve(int N) {
    for (int i = 0; i < N-1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].eb(v), adj[v].eb(u);
    }
    
    dfs(1, -1), dfs2(1, -1);
    
    int only_budded_leaf = 1, bud_cnt = 0, leaf_cnt = 0;
    for (int i = 1; i <= N; ++i) {
        if (!budded[i] and tp[i] == 0) only_budded_leaf = 0;
        bud_cnt += tp[i] == 1, leaf_cnt += tp[i] == 0;
    }
    cout << leaf_cnt - bud_cnt + only_budded_leaf << "\n";
}

void init(int N) {
    for (int i = 1; i <= N; ++i) adj[i].clear();
    tp.assign(N+1, -1), budded.assign(N+1, 0);
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        int N; cin >> N;
        init(N), solve(N);
    }
    
    return 0;
}