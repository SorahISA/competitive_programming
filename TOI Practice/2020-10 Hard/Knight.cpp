// #pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
// template <typename T>
// using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using pii = pair<int, int>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E9;
const int mod = 1E9 + 7;
const int maxn = 1000 + 5;

int dx[] = {2, 1, -1, -2, -2, -1,  1,  2};
int dy[] = {1, 2,  2,  1, -1, -2, -2, -1};

int n, m;
int board[maxn][maxn];
deque<pii> deq;

bool valid(int x, int y) {
    return 0 <= x and x < n and 0 <= y and y < m;
}

void bfs(int nx, int ny) {
    for (int i = 0; i < 8; ++i) {
        if (!valid(nx + dx[i], ny + dy[i])) continue;
        if (!board[nx + dx[i]][ny + dy[i]]) {
            board[nx + dx[i]][ny + dy[i]] = board[nx][ny] + 1;
            deq.push_back({nx + dx[i], ny + dy[i]});
        }
    }
    while (!deq.empty()) {
        pii nxt = deq.front(); deq.pop_front();
        bfs(nxt.X, nxt.Y);
    }
}

int32_t main() {
    fastIO();
    
    int sx, sy, ex, ey;
    cin >> n >> m;
    cin >> sx >> sy >> ex >> ey;
    
    board[sx][sy] = 1, bfs(sx, sy);
    cout << board[ex][ey] - 1 << "\n";
    
    return 0;
}
