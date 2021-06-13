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

const int maxn = 6E5 + 5;
const int INF = INT_MAX;

vector<pii> adj[maxn]; /// (to, dist)
vector<int> dis, vis;

void dijkstra(int st, int sz) {
    dis.assign(sz, INF), dis[st] = 0;
    vis.assign(sz, 0);
    prior<pii> pq; pq.push({0, st}); /// (dist, id)
    while (!pq.empty()) {
        int id = pq.top().Y; pq.pop();
        if (vis[id]) continue;
        vis[id] = 1;
        
        for (auto [to, dist] : adj[id]) {
            if (dis[to] > dis[id] + dist) {
                dis[to] = dis[id] + dist, pq.push({dis[to], to});
            }
        }
    }
}

void solve() {
    int L, N; cin >> L >> N;
    
    vector<int> all{0, L};
    vector<pii> bomb(N);
    for (auto &[x, d] : bomb) {
        cin >> x >> d, all.eb(x);
        if (x - d >= 0) all.eb(x - d);
        if (x + d <= L) all.eb(x + d);
    }
    sort(ALL(all)), all.resize(unique(ALL(all)) - begin(all));
    
    // cout << all << "\n";
    
    for (int i = 0; i < all.size()-1; ++i) {
        adj[i].eb(i+1, all[i+1] - all[i]);
        adj[i+1].eb(i, all[i+1] - all[i]);
    }
    
    for (auto &[x, d] : bomb) {
        int pL = lower_bound(ALL(all), x-d) - begin(all);
        int pX = lower_bound(ALL(all), x  ) - begin(all);
        int pR = lower_bound(ALL(all), x+d) - begin(all);
        if (x - d >= 0) adj[pX].eb(pL, 0);
        if (x + d <= L) adj[pX].eb(pR, 0);
    }
    
    int sz = all.size();
    vector<int> tmp;
    dijkstra(0, sz), tmp = dis, dijkstra(sz-1, sz);
    
    // cout << tmp << "\n" << dis << "\n";
    
    int ans = INF;
    for (int i = 0; i < sz; ++i) {
        ans = min(ans, max(tmp[i], dis[i]));
        if (i) {
            int d = all[i] - all[i-1];
            ans = min(ans, max(tmp[i-1], dis[i]) + (max((int)0, d - abs(tmp[i-1] - dis[i])) + 1) / 2);
            ans = min(ans, max(tmp[i], dis[i-1]) + (max((int)0, d - abs(tmp[i] - dis[i-1])) + 1) / 2);
        }
    }
    cout << ans << "\n";
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