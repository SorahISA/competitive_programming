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

const int maxn = 1E5 + 5;
const int INF = numeric_limits<int>::max() >> 3;

vector<tuple<int, int, int>> adj[maxn]; /// (to, C, D)
vector<int> dis(maxn, INF), vis(maxn, 0);

int find_min_arrive_time(int C, int D, int t) {
    int sq = max((int)floor(sqrt(D)) - 2, t), minAns = INF;
    // cout << "sq: " << sq << "\n";
    for (int i = sq; i <= sq + 4; ++i) {
        minAns = min(minAns, i + C + D / (i+1));
    }
    return minAns;
}

void dijkstra(int st) {
    prior<pii> pq; /// (minDis, id)
    dis[st] = 0, pq.push({0, st});
    
    while (!pq.empty()) {
        auto [minDis, id] = pq.top(); pq.pop();
        if (vis[id]) continue;
        vis[id] = 1;
        
        for (auto [to, C, D] : adj[id]) {
            int arrive = find_min_arrive_time(C, D, dis[id]);
            if (dis[to] > arrive) {
                dis[to] = arrive, pq.push({dis[to], to});
            }
        }
    }
}

void solve() {
    int N, M; cin >> N >> M;
    
    for (int i = 0; i < M; ++i) {
        int u, v, c, d; cin >> u >> v >> c >> d;
        adj[u].eb(v, c, d), adj[v].eb(u, c, d);
    }
    
    dijkstra(1);
    
    cout << (vis[N] ? dis[N] : (int)-1) << "\n";
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