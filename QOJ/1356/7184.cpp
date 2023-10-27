#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

const int maxc = 100;

void solve() {
    int N, T; cin >> N >> T;
    int Hx, Hy; cin >> Hx >> Hy;
    int Ex, Ey; cin >> Ex >> Ey;
    
    vector<pii> pluses(N);
    for (auto &[x, y] : pluses) cin >> x >> y;
    
    double ans0 = sqrtl((Ex-Hx)*(Ex-Hx) + (Ey-Hy)*(Ey-Hy));
    
    int ans1_p = 0;
    int min_HE_dis = 2*maxc+1;
    for (int i = 0; i < N; ++i) {
        int H_dis = min(abs(pluses[i].X - Hx), abs(pluses[i].Y - Hy));
        int E_dis = min(abs(pluses[i].X - Ex), abs(pluses[i].Y - Ey));
        if (chmin(min_HE_dis, H_dis + E_dis)) ans1_p = i+1;
    }
    double ans1 = min_HE_dis + T;
    
    int ans2_pH = 0, ans2_pE = 0;
    int min_H_dis = maxc+1, min_E_dis = maxc+1;
    for (int i = 0; i < N; ++i) {
        if (chmin(min_H_dis, abs(pluses[i].X - Hx))) ans2_pH = i+1;
        if (chmin(min_H_dis, abs(pluses[i].Y - Hy))) ans2_pH = i+1;
        if (chmin(min_E_dis, abs(pluses[i].X - Ex))) ans2_pE = i+1;
        if (chmin(min_E_dis, abs(pluses[i].Y - Ey))) ans2_pE = i+1;
    }
    double ans2 = min_H_dis + min_E_dis + 2*T;
    
    cout << fixed << setprecision(12) << min({ans0, ans1, ans2}) << "\n";
    if (ans0 <= ans1 and ans0 <= ans2) {
        cout << 1 << "\n";
        cout << 0 << " " << Ex << " " << Ey << "\n";
    }
    else if (ans1 <= ans2) {
        cout << 3 << "\n";
        if (abs(pluses[ans1_p-1].X - Hx) <= abs(pluses[ans1_p-1].Y - Hy)) {
            cout << 0 << " " << pluses[ans1_p-1].X << " " << Hy << "\n";
        }
        else {
            cout << 0 << " " << Hx << " " << pluses[ans1_p-1].Y << "\n";
        }
        if (abs(pluses[ans1_p-1].X - Ex) <= abs(pluses[ans1_p-1].Y - Ey)) {
            cout << ans1_p << " " << pluses[ans1_p-1].X << " " << Ey << "\n";
        }
        else {
            cout << ans1_p << " " << Ex << " " << pluses[ans1_p-1].Y << "\n";
        }
        cout << 0 << " " << Ex << " " << Ey << "\n";
    }
    else {
        cout << 4 << "\n";
        if (abs(pluses[ans2_pH-1].X - Hx) <= abs(pluses[ans2_pH-1].Y - Hy)) {
            cout << 0 << " " << pluses[ans2_pH-1].X << " " << Hy << "\n";
        }
        else {
            cout << 0 << " " << Hx << " " << pluses[ans2_pH-1].Y << "\n";
        }
        cout << ans2_pH << " " << pluses[ans2_pH-1].X << " " << pluses[ans2_pE-1].Y << "\n";
        if (abs(pluses[ans2_pE-1].X - Ex) <= abs(pluses[ans2_pE-1].Y - Ey)) {
            cout << ans2_pE << " " << pluses[ans2_pE-1].X << " " << Ey << "\n";
        }
        else {
            cout << ans2_pE << " " << Ex << " " << pluses[ans2_pE-1].Y << "\n";
        }
        cout << 0 << " " << Ex << " " << Ey << "\n";
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
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "%sAt [%s], line %d: (%s) = ", "\u001b[33m", __FILE__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), fprintf(stderr, "%s", "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

#endif
