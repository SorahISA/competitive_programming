#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define ef push_front
#define pf pop_front
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template <typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

vector<int> p;

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
int U(int x, int y) {x = R(x), y = R(y); return x ^ y ? p[x] = y, 1 : 0;}

void solve() {
    int N, M; cin >> N >> M, p.resize(N+M);
    
    vector<tuple<double, double, double>> pts(N+M); /// (x, y, r)
    for (int tok = 0; auto &[x, y, r] : pts) {
        if (++tok <= N) cin >> x >> y, r = 0;
        else            cin >> x >> y >> r;
    }
    
    vector<vector<double>> dis(N+M, vector<double>(N+M));
    for (int i = 0; i < N+M; ++i) {
        for (int j = i+1; j < N+M; ++j) {
            auto [x1, y1, r1] = pts[i];
            auto [x2, y2, r2] = pts[j];
            double dist = hypot(x1 - x2, y1 - y2);
            if (i >= N and j >= N) {
                if (dist + min(r1, r2) < max(r1, r2)) dis[i][j] = abs(dist - max(r1, r2) + min(r1, r2));
                else dis[i][j] = max(dist - r1 - r2, (double)0);
            }
            else {
                dis[i][j] = abs(dist - r1 - r2);
            }
        }
    }
    
    // cerr << "====== dis ======\n";
    // for (auto &vec : dis) {
        // for (double &d : vec) cerr << d << " ";
        // cerr << "\n";
    // }
    // cerr << "=================\n";
    
    double ans = 1e18;
    for (int mask = 0; mask < 1<<M; ++mask) {
        iota(ALL(p), 0);
        vector<tuple<int, int, double>> edge; /// (u, v, w)
        for (int i = 0; i < N+M; ++i) {
            if (i >= N and ~mask >> (i-N) & 1) continue;
            for (int j = i+1; j < N+M; ++j) {
                if (j >= N and ~mask >> (j-N) & 1) continue;
                edge.eb(i, j, dis[i][j]);
            }
        }
        sort(ALL(edge), [](auto &t1, auto &t2) {return get<2>(t1) < get<2>(t2);});
        
        double mst = 0.0;
        for (auto &[u, v, w] : edge) {
            if (U(u, v)) mst += w;
        }
        chmin(ans, mst);
    }
    cout << fixed << setprecision(20) << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
