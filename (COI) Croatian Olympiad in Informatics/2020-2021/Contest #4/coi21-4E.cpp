// #pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

const int INF = 1E9;
const int maxn = 4E6 + 50;

const int dx[] = {0, 1,  0, -1};
const int dy[] = {1, 0, -1,  0};
const char dc[] = ">v<^";

int n, m;
vector<string> mp;
vector<int> dis(maxn, INF), lst(maxn, -1);
prior<pii> pq;

auto trans = [&](int x, int y) {return x * m + y;};
auto valid = [&](int x, int y) {return x >= 0 and x < n and y >= 0 and y < m;};

void dijkstra(int now) {
    int i = now / m, j = now % m;
    for (int d = 0; d < 4; ++d) {
        if (!valid(i+dx[d], j+dy[d])) continue;
        int val = mp[i][j] == dc[d] or mp[i][j] == 'o' ? 0 : 1;
        int id = trans(i+dx[d], j+dy[d]);
        if (dis[id] > dis[now] + val) {
            dis[id] = dis[now] + val, lst[id] = now;
            pq.push({dis[id], id});
        }
    }
    while (!pq.empty()) {
        auto [val, id] = pq.top(); pq.pop();
        if (val == dis[id]) dijkstra(id);
    }
}

void solve() {
    cin >> n >> m, mp.resize(n);
    for (auto &str : mp) cin >> str;
    
    int st, ed;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mp[i][j] == 'o') st = trans(i, j);
            if (mp[i][j] == 'x') ed = trans(i, j);
        }
    }
    
    dis[st] = 0, dijkstra(st);
    // cout << st << " " << ed << "\n";
    // for (int i = 0; i < n*m; ++i) cout << dis[i] << " \n"[(i+1) % m == 0];
    
    int nx = ed / m, ny = ed % m, now = ed;
    while ((now = trans(nx, ny)) != st) {
        /// >v<^ --- 0 <-> 2; 1 <-> 3 ///
        // cout << nx << " " << ny << "\n";
        for (int d = 0; d < 4; ++d) {
            if (trans(nx+dx[d], ny+dy[d]) != lst[now]) continue;
            nx = lst[now] / m, ny = lst[now] % m;
            if (mp[nx][ny] != 'o') mp[nx][ny] = dc[d^2];
            break;
        }
    }
    
    cout << dis[ed] << "\n";
    for (auto str : mp) cout << str << "\n";
}

int32_t main() {
    // fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
