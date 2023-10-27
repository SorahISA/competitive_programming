#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

void solve() {
    int N, M; cin >> N >> M;
    
    vector<string> grid(N);
    for (string &str : grid) cin >> str;
    
    vector indices(N, vector(M, vector<int>()));
    vector<pii> index_mapping;
    int index_tok = 0;
    for (int i = 0; i < N-1; ++i) {
        for (int j = 0; j < M; ++j) {
            if (grid[i][j] == '.' or grid[i][j] != grid[i+1][j]) continue;
            if (isupper(grid[i][j])) {
                if (j+1 < M and grid[i][j+1] == '.' and grid[i+1][j+1] == '.') {
                    index_mapping.eb(i, j);
                    indices[i  ][j  ].eb(index_tok);
                    indices[i+1][j  ].eb(index_tok);
                    indices[i  ][j+1].eb(index_tok);
                    indices[i+1][j+1].eb(index_tok);
                    ++index_tok;
                }
            }
            else {
                if (j-1 >= 0 and grid[i][j-1] == '.' and grid[i+1][j-1] == '.') {
                    index_mapping.eb(i, j-1);
                    indices[i  ][j  ].eb(index_tok);
                    indices[i+1][j  ].eb(index_tok);
                    indices[i  ][j-1].eb(index_tok);
                    indices[i+1][j-1].eb(index_tok);
                    ++index_tok;
                }
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M-1; ++j) {
            if (grid[i][j] == '.' or grid[i][j] != grid[i][j+1]) continue;
            if (isupper(grid[i][j])) {
                if (i+1 < N and grid[i+1][j] == '.' and grid[i+1][j+1] == '.') {
                    index_mapping.eb(i, j);
                    indices[i  ][j  ].eb(index_tok);
                    indices[i  ][j+1].eb(index_tok);
                    indices[i+1][j  ].eb(index_tok);
                    indices[i+1][j+1].eb(index_tok);
                    ++index_tok;
                }
            }
            else {
                if (i-1 >= 0 and grid[i-1][j] == '.' and grid[i-1][j+1] == '.') {
                    index_mapping.eb(i-1, j);
                    indices[i  ][j  ].eb(index_tok);
                    indices[i  ][j+1].eb(index_tok);
                    indices[i-1][j  ].eb(index_tok);
                    indices[i-1][j+1].eb(index_tok);
                    ++index_tok;
                }
            }
        }
    }
    
    // debug("ALIVE");
    
    vector<vector<int>> adj(index_tok);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            assert(SZ(indices[i][j]) <= 2);
            if (SZ(indices[i][j]) == 2) {
                adj[indices[i][j][0]].eb(indices[i][j][1]);
                adj[indices[i][j][1]].eb(indices[i][j][0]);
            }
        }
    }
    
    // debug("ALIVE");
    
    vector<int> vis(index_tok, 0);
    auto dfs = [&](int st) -> vector<int> {
        vector<int> path;
        deque<int> deq{st};
        while (SZ(deq)) {
            int now = deq[0]; deq.pf();
            if (vis[now]) continue;
            vis[now] = 1, path.eb(now);
            for (int x : adj[now]) {if (!vis[x]) deq.ef(x);}
        }
        return path;
    };
    
    vector<int> unroll;
    for (int i = 0; i < index_tok; ++i) {
        if (vis[i] or SZ(adj[i]) > 1) continue;
        auto path = dfs(i);
        for (int j = 0; j < SZ(path); j += 2) unroll.eb(path[j]);
        // debug(i, path);
    }
    for (int i = 0; i < index_tok; ++i) {
        if (vis[i]) continue;
        auto path = dfs(i);
        for (int j = 1; j < SZ(path); j += 2) unroll.eb(path[j]);
        // debug(i, path);
    }
    
    // debug("ALIVE");
    
    for (int i : unroll) {
        auto [x, y] = index_mapping[i];
        char num = '1' + (3*(x%3) + (y%3));
        grid[x][y] = grid[x][y+1] = grid[x+1][y] = grid[x+1][y+1] = num;
    }
    
    for (int i = 0; i < N-1; ++i) {
        for (int j = 0; j < M; ++j) {
            if (!isalpha(grid[i][j]) or grid[i][j] != grid[i+1][j]) continue;
            char num = '1' + (3*(i%3) + (j%3));
            grid[i][j] = grid[i+1][j] = num;
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M-1; ++j) {
            if (!isalpha(grid[i][j]) or grid[i][j] != grid[i][j+1]) continue;
            char num = '1' + (3*(i%3) + (j%3));
            grid[i][j] = grid[i][j+1] = num;
        }
    }
    
    cout << SZ(unroll) << "\n";
    for (int i = 0; i < N; ++i) cout << grid[i] << "\n";
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
// #define double __float80
using pii = pair<int, int>;
template <typename T> using MaxHeap = std::priority_queue<T>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)

template <typename T>
ostream & operator << (ostream &os, const vector<T> &vec) {
    os << "[";
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << ", ";
        os << vec[i];
    }
    os << "]";
    return os;
}

#ifdef local
#define IOS() void()
#define debug(...) \
    fprintf(stderr, "%sAt [%s], line %d: (%s) = ", "\u001b[33m", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), fprintf(stderr, "%s", "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#define debug(...) void()
#define endl '\n'
#endif

// mt19937_64 rng(steady::chrono_clock::now().time_since_epoch().count());

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

#endif
