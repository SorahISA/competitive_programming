#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double __float80
using pii = pair<int, int>;
template <typename T> using MaxHeap = std::priority_queue<T>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;

template <size_t D, typename T> struct Vec : vector<Vec<D-1, T>> {
    template <typename ...U> Vec(int n = 0, U ..._u) :
        vector<Vec<D-1, T>>(n, Vec<D-1, T>(_u...)) {}
};

template <typename T> struct Vec<1, T> : vector<T> {
    Vec(int n = 0, const T &val = T()) :
        vector<T>(n, val) {}
};

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

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\e[1;93mAt [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), fprintf(stderr, "\e[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
// #define endl "\n"
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int INF = LLONG_MAX >> 2;

int area(pii p1, pii p2, pii p3) {
    return abs((p1.X * p2.Y + p2.X * p3.Y + p3.X * p1.Y) - (p1.Y * p2.X + p2.Y * p3.X + p3.Y * p1.X));
}

void solve() {
    int N; cin >> N;
    
    vector<pii> pts(N);
    for (int i = 0; i < N; ++i) cin >> pts[i].X >> pts[i].Y;
    
    int sz = N;
    vector<int> alive;
    for (int i = 0; i < N; ++i) alive.eb(i);
    
    int id;
    if (N % 2 == 0) {
        cout << "Alberto" << endl;
        for (int i = 0, meow = INF; i < sz; ++i) {
            if (chmin(meow, area(pts[alive[i]], pts[alive[(i+1)%sz]], pts[alive[(i+2)%sz]]))) id = alive[(i+1)%sz];
        }
        cout << id + 1 << endl;
        alive.erase(find(ALL(alive), id)), --sz;
    }
    else {
        cout << "Beatrice" << endl;
    }
    
    while (sz >= 3) {
        int op; cin >> op, --op;
        alive.erase(find(ALL(alive), op)), --sz;
        if (sz < 3) break;
        
        for (int i = 0, meow = INF; i < sz; ++i) {
            if (chmin(meow, area(pts[alive[i]], pts[alive[(i+1)%sz]], pts[alive[(i+2)%sz]]))) id = alive[(i+1)%sz];
        }
        cout << id + 1 << endl;
        alive.erase(find(ALL(alive), id)), --sz;
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
