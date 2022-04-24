#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define eb emplace_back
#define ef push_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    cerr << "\u001b[33m" << "At [" << __FUNCTION__ << "], line " << __LINE__ << ", ",\
    cerr << "(" << #__VA_ARGS__ << ") = ", _do(__VA_ARGS__), cerr << "\u001b[0m"
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    vector<tuple<int, int, int>> skill(N);
    for (auto &[X, Y, Z] : skill) cin >> X >> Y >> Z;
    
    deque<int> id_x(N), id_y, id_z;
    iota(ALL(id_x), 0), id_y = id_z = id_x;
    sort(ALL(id_x), [&](int x, int y) {return get<0>(skill[x]) > get<0>(skill[y]);});
    sort(ALL(id_y), [&](int x, int y) {return get<1>(skill[x]) > get<1>(skill[y]);});
    sort(ALL(id_z), [&](int x, int y) {return get<2>(skill[x]) > get<2>(skill[y]);});
    
    vector<int> alive(N, 1);
    while (true) {
        while (SZ(id_x) and !alive[id_x[0]]) id_x.pf();
        while (SZ(id_y) and !alive[id_y[0]]) id_y.pf();
        while (SZ(id_z) and !alive[id_z[0]]) id_z.pf();
        if (!SZ(id_x) or !SZ(id_y) or !SZ(id_z)) return cout << -1 << "\n", void();
        
        auto &[xx, xy, xz] = skill[id_x[0]];
        auto &[yx, yy, yz] = skill[id_y[0]];
        auto &[zx, zy, zz] = skill[id_z[0]];
        int flag = 0;
        
        if (xy == yy or xz == zz) alive[id_x[0]] = 0, flag = 1;
        if (yx == xx or yz == zz) alive[id_y[0]] = 0, flag = 1;
        if (zx == xx or zy == yy) alive[id_z[0]] = 0, flag = 1;
        
        if (flag) continue;
        return cout << xx + yy + zz << "\n", void();
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
