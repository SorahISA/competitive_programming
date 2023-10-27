#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

pii operator + (pii a, pii b) {return pii(a.X + b.X, a.Y + b.Y);}
pii operator - (pii a, pii b) {return pii(a.X - b.X, a.Y - b.Y);}
int dot(pii a, pii b) {return a.X * b.X + a.Y * b.Y;}
int cross(pii a, pii b) {return a.X * b.Y - a.Y * b.X;}
int sign(int x) {return clamp(x, int(-1), int(+1));}
int ori(pii a, pii b, pii c) {return sign(cross(b-a, c-a));}
bool coll(pii a, pii b, pii c) {return (ori(a, b, c) == 0);}
bool btw(pii a, pii b, pii c) {return (coll(a, b, c) ? (sign(dot(a-c, b-c)) <= 0) : 0);}
bool seg_intersect(pii a, pii b, pii c, pii d) {
    int a123 = ori(a, b, c), a124 = ori(a, b, d), a341 = ori(c, d, a), a342 = ori(c, d, b);
    if (a123 == 0 and a124 == 0) return (btw(a, b, c) or btw(a, b, d) or btw(c, d, a) or btw(c, d, b));
    return (a123 * a124 < 0 and a341 * a342 < 0);
}

int hull_size(vector<pii> dots) {
    sort(ALL(dots));
    vector<pii> ans{dots[0]};
    for (int ct = 0; ct < 2; ++ct, reverse(ALL(dots))) {
        for (int i = 1, t = SZ(ans); i < SZ(dots); ans.eb(dots[i++])) {
            while (SZ(ans) > t and ori(end(ans)[-2], end(ans)[-1], dots[i]) <= 0) ans.pb();
        }
    }
    return SZ(ans) - 1;
}

void solve() {
    int N; cin >> N;
    
    vector<pii> pts(N);
    for (auto &[x, y] : pts) cin >> x >> y;
    
    /// E = 3n - |CV| - 3 ///
    
    int E = 3*N - hull_size(pts) - 3;
    // debug(E);
    
    set<pii> alives;
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) alives.ee(i, j);
    }
    
    auto rem = [&](int i, int j) -> void {
        auto it = begin(alives);
        while (it != end(alives)) {
            while (it != end(alives) and seg_intersect(pts[i], pts[j], pts[it->first], pts[it->second])) {
                // debug(i, j, it->first, it->second);
                it = alives.erase(it);
            }
            if (it != end(alives)) it = next(it);
        }
    };
    
    if (E % 2 == 1) {
        cout << 1 << "\n" << flush;
    }
    else {
        cout << 2 << "\n" << flush;
        int i, j; cin >> i >> j;
        rem(i-1, j-1);
    }
    
    while (SZ(alives)) {
        auto [i, j] = *begin(alives);
        cout << i+1 << " " << j+1 << "\n" << flush;
        rem(i, j);
        cin >> i >> j;
        if (i == 0 and j == 0) return;
        rem(i-1, j-1);
    }
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

#define X first
#define Y second
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)

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
