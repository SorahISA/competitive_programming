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

template<typename T>
ostream &operator << (ostream &os, const vector<T> &v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i) os << " ";
        os << v[i];
    }
    return os;
}

template<typename T>
ostream &operator << (ostream &os, const vector<pair<T, T>> &v) {
    for (int i = 0; i < v.size(); ++i) {
        if (i) os << "\n";
        os << v[i].first << " " << v[i].second;
    }
    return os;
}

const int INF = INT_MAX;

void solve() {
    int N; cin >> N;
    
    vector<pii> coord(N);
    for (auto &[x, y] : coord) cin >> x >> y;
    
    vector<int> build(N), line(N);
    for (auto &x : build) cin >> x;
    for (auto &x : line) cin >> x;
    
    auto calc = [&](int x, int y) -> int {
        return (line[x] + line[y]) * (abs(coord[x].X - coord[y].X) + abs(coord[x].Y - coord[y].Y));
    };
    
    int cost = 0;
    vector<int> vertex;
    vector<pii> edge;
    
    vector<int> vis(N, 0);
    vector<pii> dis(N); /// (dist, from)
    for (int i = 0; i < N; ++i) dis[i] = {build[i], i};
    
    for (int cnt = 0; cnt < N; ++cnt) {
        int min_dis = INF, min_dis_id = -1;
        for (int i = 0; i < N; ++i) {
            if (!vis[i] and dis[i].X < min_dis) min_dis = dis[i].X, min_dis_id = i;
        }
        cost += min_dis;
        if (dis[min_dis_id].Y == min_dis_id) vertex.eb(min_dis_id + 1);
        else edge.eb(min_dis_id + 1, dis[min_dis_id].Y + 1);
        
        int now = min_dis_id;
        dis[now].X = 0, vis[now] = 1;
        for (int i = 0; i < N; ++i) {
            if (dis[i].X <= dis[now].X + calc(now, i)) continue;
            dis[i] = {dis[now].X + calc(now, i), now};
        }
    }
    
    cout << cost << "\n";
    cout << vertex.size() << "\n" << vertex << "\n";
    cout << edge.size() << "\n" << edge << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}