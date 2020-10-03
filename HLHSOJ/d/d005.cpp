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

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 1000 + 5;

vector<int> p;
int dis[maxn][maxn];

int R(int x) {return p[x] ^ x ? p[x] = R(p[x]) : x;}
void U(int x, int y) {p[R(x)] = R(y);}

int32_t main() {
    fastIO();
    memset(dis, 0x3f, sizeof(dis));
    
    int n, m;
    cin >> n >> m, p.resize(n + 1), iota(ALL(p), 0);
    
    for (int i = 1; i <= n; ++i) dis[i][i] = 0;
    
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w, U(u, v);
        dis[u][v] = min(dis[u][v], w);
        dis[v][u] = min(dis[v][u], w);
    }
    
    map<int, int> minId; /// (rt, id)
    for (int i = n; i >= 1; --i) minId[R(i)] = i;
    
    vector<int> trans;
    for (auto id : minId) trans.eb(id.Y);
    
    int sz = trans.size();
    for (int i = 0; i < sz; ++i) {
        dis[trans[i]][trans[(i+1)%sz]] = 0;
        dis[trans[(i+1)%sz]][trans[i]] = 0;
    }
    
    for (int l = 1; l <= n; ++l) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                dis[i][j] = min(dis[i][j], dis[i][l] + dis[l][j]);
            }
        }
    }
    
    int k, lst, now, ans = 0;
    cin >> k >> now;
    
    for (int i = 1; i < k; ++i) {
        lst = now;
        cin >> now;
        ans += dis[lst][now];
    }
    
    cout << ans << "\n";
    
    return 0;
}
