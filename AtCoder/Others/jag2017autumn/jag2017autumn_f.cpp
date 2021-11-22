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

const int dx[] = {1, 0, -1,  0};
const int dy[] = {0, 1,  0, -1};

int H, W;
vector<string> maze;

bool valid(int x, int y) {
    return (0 <= x and x < H and
            0 <= y and y < W and
            (maze[x][y] == '#' or maze[x][y] == '*'));
}

void dfs(int x, int y, int &flag) {
    if (maze[x][y] == '*') return flag = 1, void();
    if (maze[x][y] != '@') maze[x][y] = '.';
    for (int d : {0, 1, 2, 3}) {
        if (valid(x+dx[d], y+dy[d])) dfs(x+dx[d], y+dy[d], flag);
        if (flag) return;
    }
}

void solve() {
    cin >> H >> W;
    
    maze.resize(H);
    for (auto &str : maze) cin >> str;
    
    if (H == 3) {
        for (int i : {0, 2}) {
            for (int j = 0; j < W; ++j) {
                if (maze[i][j] == '.') maze[i][j] = '#';
            }
        }
        maze[1][0] = maze[1][W-1] = '#';
    }
    else if (W == 3) {
        for (int i = 0; i < H; ++i) {
            for (int j : {0, 2}) {
                if (maze[i][j] == '.') maze[i][j] = '#';
            }
        }
        maze[0][1] = maze[H-1][1] = '#';
    }
    else {
        maze[0][1] = maze[H-1][1] = '#';
        for (int i = 0; i < H; ++i) {
            if (maze[i][0] == '.') maze[i][0] = '#';
            if (i & 1) {
                if (i & 2) maze[i][2] = '#';
                else       maze[i][W-1] = '#';
            }
        }
        for (int i = 0; i < H; i += 2) {
            for (int j = 2; j < W; ++j) {
                if (maze[i][j] == '.') maze[i][j] = '#';
            }
        }
    }
    
    int sx = -1, sy = -1, flag = 0;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            if (maze[i][j] == '@') {sx = i, sy = j; break;}
        }
    }
    dfs(sx, sy, flag);
    
    
    for (auto str : maze) cout << str << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}