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

const int maxn = 105;

int mx[] = {0, 0, 1, -1};
int my[] = {1, -1, 0, 0};

bitset<maxn> vis[maxn];
bool chk[4][128][128];
int val[maxn][maxn];
string mp[maxn];
int n, m;

bool in(int x, int y) {
    return (0 <= x && x < n) && (0 <= y && y < m);
}

void solve() {
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> mp[i];
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> val[i][j];
        }
    }
    for(int i = 0; i < 2; i++) {
        chk[i]['+']['-'] = 1;
        chk[i]['-']['+'] = 1;
        chk[i]['+']['+'] = 1;
        chk[i]['-']['-'] = 1;
    }
    for(int i = 2; i < 4; i++) {
        chk[i]['+']['|'] = 1;
        chk[i]['|']['+'] = 1;
        chk[i]['+']['+'] = 1;
        chk[i]['|']['|'] = 1;
    }
    int a, b, c, D;
    cin >> a >> b >> c >> D;
    queue<pii> que;
    que.emplace(a, b);
    vis[a][b] = 1;
    while(SZ(que)) {
        int x = que.front().X;
        int y = que.front().Y;
        que.pop();
        debug(x, y);
        for(int d = 0; d < 4; d++) {
            int xx = x + mx[d];
            int yy = y + my[d];
            if(in(xx, yy) && !vis[xx][yy] && val[xx][yy] <= val[x][y] && chk[d][mp[x][y]][mp[xx][yy]]) {
                que.emplace(xx, yy); vis[xx][yy] = 1;
            }
        }
    }
    cout << (vis[c][D] ? "YES" : "NO") << '\n'; 
}

signed main() {
    IOS();
    int _ = 1;
    // cin >> _;
    for (int i=1;i<=_;++i) {
        solve();
    }
}
