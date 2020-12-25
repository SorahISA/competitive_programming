#pragma GCC optimize("Ofast", "unroll-loops")

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

const int maxn = 1000 + 5;
// const int INF = 0x3f3f3f3f3f3f3f3f;
const int INF = 0x3f3f3f3f;
const int dx[] = {1, 0, -1,  0};
const int dy[] = {0, 1,  0, -1};

int n, D;
int valve[maxn][maxn], dis[maxn][maxn], ans[maxn][maxn];
vector<string> mp;
deque<pii> deq;
Prior<pair<int, pii>> pq;

int valid(int x, int y) {
    return 0 <= x and x < n and 0 <= y and y < n and mp[x][y] != '#';
}

void bfs_valve() {
    while (!deq.empty()) {
        auto x = deq.front().X, y = deq.front().Y; deq.pop_front();
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (valid(nx, ny) and valve[nx][ny] == 0) {
                valve[nx][ny] = valve[x][y] + D, deq.eb(nx, ny);
            }
        }
    }
}

void bfs_dis() {
    while (!deq.empty()) {
        auto x = deq.front().X, y = deq.front().Y; deq.pop_front();
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (valid(nx, ny) and dis[nx][ny] == INF and dis[x][y] < valve[nx][ny]) {
                dis[nx][ny] = min(dis[nx][ny], dis[x][y] + 1);
                if (dis[nx][ny] < valve[nx][ny]) deq.eb(nx, ny);
            }
        }
    }
}

void bfs_ans() {
    while (!pq.empty()) {
        auto L = pq.top().X, x = pq.top().Y.X, y = pq.top().Y.Y; pq.pop();
        if (L == 0) continue;
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (valid(nx, ny) and ans[nx][ny] == 0) {
                pq.push({L-1, pii{nx, ny}});
                ans[nx][ny] = 1;
            }
        }
    }
}

void solve() {
    memset(valve, 0x00, sizeof(valve));
    memset(dis, 0x3f, sizeof(dis));
    memset(ans, 0x00, sizeof(ans));
    
    cin >> n >> D, mp.resize(n);
    D = min(D, (int)1000);
    for (auto &str : mp) cin >> str;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mp[i][j] == '#') deq.eb(i, j);
        }
    }
    bfs_valve();
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mp[i][j] == 'S') dis[i][j] = 0, deq.eb(i, j);
        }
    }
    bfs_dis();
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mp[i][j] != '#' and (mp[i][j] == 'S' or dis[i][j] != INF)) {
                pq.push({dis[i][j] / D - (dis[i][j] == valve[i][j]), pii{i, j}});
                ans[i][j] = 1;
            }
        }
    }
    bfs_ans();
    
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (ans[i][j] == 1) ++cnt;
            // cout << (ans[i][j] ? 'x' : (mp[i][j] == '#' ? '#' : '.')) << " \n"[j == n-1];
        }
    }
    cout << cnt << "\n";
    
    /* for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(2) << valve[i][j] << " \n"[j == n-1];
        }
    }
    cout << string(3*n-1, '=') << "\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(2) << (dis[i][j] == INF ? -1 : dis[i][j]) << " \n"[j == n-1];
        }
    } */
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
