#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define eb emplace_back
#define X first
#define Y second
#ifdef local
#define debug(...) do{\
    fprintf(stderr, "LINE %d: (%s) = ", __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template <typename T> void _do(T &&_x) {cerr << _x << endl;}
template <typename T, typename ...S> void _do(T &&_x, S &&..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs){return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs){return lhs < rhs ? lhs = rhs, 1 : 0;}

const pii dir[] = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}
};

void solve() {
    int n, m; cin >> n >> m;
    if (n == 0 or m == 0) return;
    
    auto valid = [&](int x, int y) -> bool {
        if (x < 0 or x >= n) return false;
        if (y < 0 or y >= m) return false;
        return true;
    };
    
    vector<vector<int>> board(n, vector<int>(m, -1));
    int tok = 0, d = 0, cx = 0, cy = 0;
    while (tok < n*m) {
        board[cx][cy] = tok++;
        int nx = cx + dir[d].X, ny = cy + dir[d].Y;
        if (valid(nx, ny) and board[nx][ny] == -1) cx = nx, cy = ny;
        else d = (d+1)%4, cx += dir[d].X, cy += dir[d].Y;
    }
    
    for (vector<int> &vec : board) {
        for (int &x : vec) cout << x << " ";
        cout << "\n";
    }
}

signed main() {
    IOS();
    int _ = 1;
    // cin >> _;
    for (int i=1;i<=_;++i) {
        solve();
    }
}
