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

const int maxm = 2E5 + 5;
const int INF = INT_MAX;

vector<pii> x_axis[2*maxm]; /// (x, id)
vector<int> adj[maxm], vis(maxm, 0);

void dfs(int now) {
    vis[now] = 1;
    for (auto x : adj[now]) if (!vis[x]) dfs(x);
}

void solve() {
    int N, M; cin >> N >> M;
    
    x_axis[maxm].eb(0, 0);
    for (int i = 0; i < M; ++i) {
        int x, y; cin >> x >> y;
        if (-maxm < y-N and y-N < maxm) x_axis[maxm+y-N].eb(x, i+1);
    }
    for (int i = 0; i < 2*maxm; ++i) sort(ALL(x_axis[i]));
    
    for (int i = 1; i < 2*maxm-1; ++i) {
        for (int j = 0, tokL = 0, tokR = 0; j < x_axis[i].size(); ++j) {
            auto [x, id] = x_axis[i][j];
            
            while (tokL+1 < x_axis[i-1].size() and x_axis[i-1][tokL+1].X < x) ++tokL;
            if (x_axis[i-1].size() and x_axis[i-1][tokL].X < x) adj[x_axis[i-1][tokL].Y].eb(id);
            
            while (tokR+1 < x_axis[i+1].size() and x_axis[i+1][tokR+1].X < x) ++tokR;
            if (x_axis[i+1].size() and x_axis[i+1][tokR].X < x) adj[x_axis[i+1][tokR].Y].eb(id);
        }
    }
    dfs(0);
    
    int cnt = 0;
    for (int i = 1; i < 2*maxm-1; ++i) {
        if (x_axis[i].size() and vis[x_axis[i].back().Y]) ++cnt;
    }
    cout << cnt << "\n";
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