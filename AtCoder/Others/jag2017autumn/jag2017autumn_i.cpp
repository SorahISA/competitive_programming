#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T> using Prior = std::priority_queue<T>;
template<typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &x, T y) {return x > y ? x = y, 1 : 0;}
template<typename T> bool chmax(T &x, T y) {return x < y ? x = y, 1 : 0;}

const int maxn = 500 + 5;

bitset<maxn> adj[maxn];

int endless_bfs(int N) {
    int cnt = 0;
    bitset<maxn> current;
    current[1] = 1;
    while (current.count() < N) {
        if (++cnt > N*N) return -1;
        bitset<maxn> found;
        for (int i = 1; i <= N; ++i) {
            if (current[i]) found |= adj[i];
        }
        current = found;
    }
    return cnt;
}

void solve() {
    int N, M; cin >> N >> M;
    
    for (int i = 0; i < M; ++i) {
        int u, v; cin >> u >> v, adj[u][v] = 1;
    }
    
    cout << endless_bfs(N) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}