#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int INF = INT_MAX;
const int maxc = 10;
const int maxd = 6 + 1;

array<array<int, maxc>, maxc> dist;

void solve() {
    int M, R; cin >> M >> R;
    
    vector<int> dis(M * maxc, INF); dis[0] = 0;
    vector<int> vis(M * maxc, 0);
    int sz = 1, tok = 0;
    vector<deque<int>> que(maxd); que[dis[0] % maxd].eb(0);
    while (sz) {
        if (!SZ(que[tok])) { tok = (tok + 1) % maxd; continue; }
        int now = que[tok][0]; que[tok].pf(), --sz;
        if (vis[now]) continue;
        vis[now] = 1;
        
        int val = now / maxc, key = now % maxc;
        for (int nxt = 0; nxt < maxc; ++nxt) {
            int x = (val * maxc + nxt) % M * maxc + nxt;
            if (chmin(dis[x], dis[now] + dist[key][nxt])) que[dis[x] % maxd].eb(x), ++sz;
        }
    }
    
    cout << *min_element(begin(dis) + R * maxc, begin(dis) + (R+1) * maxc) << "\n";
    
    // for (int c = R*maxc; c < (R+1)*maxc; ++c) debug(c%maxc, dis[c]);
}

void init() {
    array<int, maxc> row{0, 1, 1, 1, 2, 2, 2, 3, 3, 3};
    array<int, maxc> col{0, 0, 1, 2, 0, 1, 2, 0, 1, 2};
    for (int i = 0; i < maxc; ++i) for (int j = 0; j < maxc; ++j) {
        dist[i][j] = abs(row[i] - row[j]) + abs(col[i] - col[j]) + 1;
        // chmax(maxd, dist[i][j]);
    }
}

int32_t main() {
    fastIO();
    init();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
#define int int64
using float80 = long double;
#define double float80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) { cerr << _t << "\n"; }
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) { cerr << _t << ", ", _do(_u...); }
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

#endif
