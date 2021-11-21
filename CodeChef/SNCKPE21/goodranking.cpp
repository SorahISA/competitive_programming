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
#define ef push_front
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

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int maxn = 1'000 + 5;

vector<int> adj[maxn], deg_I, vis, topo;

void WA() {
    cout << -1 << "\n";
}

void dfs(int now) {
    topo.eb(now);
    for (int x : adj[now]) {
        if (++vis[x] == deg_I[x]) dfs(x);
    }
}

void solve() {
    int N; cin >> N;
    
    vector<string> vec(N);
    for (string &str : vec) cin >> str;
    
    vector<int> win_idx, los_idx;
    for (int i = 0; i < N; ++i) {
        if (count_if(ALL(vec[i]), [](char &c) {return c == '1';}) >= (N+1) / 2) {
            win_idx.eb(i+1);
        }
        else {
            los_idx.eb(i+1);
        }
    }
    
    if (SZ(win_idx) != N / 2 or SZ(los_idx) != (N+1) / 2) return WA();
    
    for (int i = 1; i <= N; ++i) adj[i].clear();
    deg_I.assign(N+1, 0), vis.assign(N+1, 0), topo.clear();
    
    for (int i : win_idx) {
        for (int j : win_idx) {
            if (vec[i-1][j-1] == '1') adj[i].eb(j), ++deg_I[j];
        }
    }
    
    for (int i : los_idx) {
        for (int j : los_idx) {
            if (vec[i-1][j-1] == '1') adj[i].eb(j), ++deg_I[j];
        }
    }
    
    for (int i : win_idx) if (deg_I[i] == 0) dfs(i);
    for (int i : los_idx) if (deg_I[i] == 0) dfs(i);
    
    if (SZ(topo) != N) return WA();
    
    for (int i = 1; i <= N; ++i) {
        for (int j = i+1; j <= min(i+(N+1)/2, N); ++j) {
            if (vec[topo[i-1]-1][topo[j-1]-1] == '0') return WA();
        }
    }
    
    cout << topo << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}
