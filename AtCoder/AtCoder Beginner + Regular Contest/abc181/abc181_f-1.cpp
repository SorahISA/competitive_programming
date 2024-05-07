#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
#define SZ(x) ((int)(x).size())
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

vector<int> p;

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
int U(int x, int y) {x = R(x), y = R(y); return x ^ y ? p[x] = y, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    vector<pii> points(N);
    for (auto &[x, y] : points) cin >> x >> y;
    
    auto get_dis2 = [&](int i, int j) -> int {
        return (points[i].X - points[j].X) * (points[i].X - points[j].X)
             + (points[i].Y - points[j].Y) * (points[i].Y - points[j].Y);
    };
    
    vector<pair<int, pii>> dis2;
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) dis2.eb(get_dis2(i, j), pair{i, j});
    }
    for (int i = 0; i < N; ++i) dis2.eb(( 100 - points[i].Y) * ( 100 - points[i].Y), pair{i, N});
    for (int i = 0; i < N; ++i) dis2.eb((-100 - points[i].Y) * (-100 - points[i].Y), pair{i, N+1});
    dis2.eb(200 * 200, pair{N, N+1});
    sort(ALL(dis2));
    
    p.resize(N+2), iota(ALL(p), 0);
    for (auto [d2, edge] : dis2) {
        // cerr << "edge: " << d2 << " " << edge.X << " " << edge.Y << "\n";
        U(edge.X, edge.Y);
        if (R(N) == R(N+1)) {
            // cout << d2 << "\n";
            cout << fixed << setprecision(10) << sqrtl(d2) / 2.0 << "\n";
            return;
        }
    }
    
}

int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
