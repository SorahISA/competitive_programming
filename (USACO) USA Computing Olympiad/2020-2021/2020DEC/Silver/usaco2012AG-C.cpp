#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
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

bitset<maxn> state;
vector<int> adj[maxn];

int dist(pii a, pii b) {
    return abs(a.X - b.X) + abs(a.Y - b.Y);
}

void dfs(int now) {
    state[now] = 1;
    for (auto x : adj[now]) {
        if (!state[x]) dfs(x);
    }
}

void solve() {
    int n; cin >> n;
    
    vector<pair<char, pii>> cow(n);
    for (auto &c : cow) cin >> c.X >> c.Y.X >> c.Y.Y;
    
    int block[n][n]; /// i block j at time block[i][j]
    for (int i = 0; i < n; ++i) {
        block[i][i] = -1;
        for (int j = i+1; j < n; ++j) {
            block[i][j] = block[j][i] = -1;
            
            int mX = max(cow[i].Y.X, cow[j].Y.X);
            int mY = max(cow[i].Y.Y, cow[j].Y.Y);
            if (cow[i].X == cow[j].X) continue;
            if (cow[i].Y.X != mX and cow[i].Y.Y != mY) continue;
            if (cow[j].Y.X != mX and cow[j].Y.Y != mY) continue;
            if (cow[i].Y.Y != mY and cow[i].X != 'N') continue;
            if (cow[j].Y.Y != mY and cow[j].X != 'N') continue;
            if (cow[i].Y.X != mX and cow[i].X != 'E') continue;
            if (cow[j].Y.X != mX and cow[j].X != 'E') continue;
            
            if (dist(cow[i].Y, {mX, mY}) < dist(cow[j].Y, {mX, mY})) {
                block[i][j] = dist(cow[j].Y, {mX, mY});
            }
            else if (dist(cow[j].Y, {mX, mY}) < dist(cow[i].Y, {mX, mY})) {
                block[j][i] = dist(cow[i].Y, {mX, mY});
            }
        }
    }
    
    prior<pair<int, pii>> pq;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (block[i][j] != -1) pq.push({block[i][j], pii{i, j}});
        }
    }
    
    vector<pii> ans(n, {-1, INT_MAX});
    while (!pq.empty()) {
        auto t = pq.top().X;
        auto blk = pq.top().Y; pq.pop();
        // cout << t << " " << blk.X << " " << blk.Y << " ";
        int mX = max(cow[blk.X].Y.X, cow[blk.Y].Y.X);
        int mY = max(cow[blk.X].Y.Y, cow[blk.Y].Y.Y);
        // cout << dist(cow[blk.X].Y, {mX, mY}) << "\n";
        if (dist(cow[blk.X].Y, {mX, mY}) > ans[blk.X].Y) continue;
        if (ans[blk.Y].Y > t) ans[blk.Y] = {blk.X, t};
    }
    
    // for (auto x : ans) cout << x.X+1 << " " << x.Y << "\n";
    
    for (int i = 0; i < n; ++i) {
        if (ans[i].X != -1) adj[ans[i].X].eb(i);
    }
    
    for (int i = 0; i < n; ++i) state.reset(), dfs(i), cout << state.count() - 1 << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
