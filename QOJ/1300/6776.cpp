#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

void solve() {
    int N, M, D; cin >> N >> M >> D;
    
    vector<pii> A(N), B(M);
    for (auto &[x, y] : A) cin >> x >> y;
    for (auto &[x, y] : B) cin >> x >> y;
    
    /// store A as row and col ///
    
    vector<int> row_A;
    vector<bool> col_A(D, 0);
    for (const pii &a : A) row_A.eb(a.X), row_A.eb(a.X + D), col_A[a.Y] = 1;
    sort(ALL(row_A)), row_A.erase(unique(ALL(row_A)), end(row_A));
    
    /// store B as vectors for each row ///
    
    vector<vector<int>> col_B(D);
    for (const pii &b : B) col_B[b.Y].eb(b.X), col_B[b.Y].eb(b.X + D);
    for (int y = 0; y < D; ++y) sort(ALL(col_B[y])), col_B[y].erase(unique(ALL(col_B[y])), end(col_B[y]));
    
    /// precalcluate many things ///
    
    int tmp_col_tmp = D;
    vector<int> ptr_l_tmp(2*D), ptr_r_tmp(2*D);
    for (int i = 0; i < 2*D; ++i) ptr_l_tmp[i] = i-1, ptr_r_tmp[i] = i+1;
    
    for (int y = 0; y < D; ++y) {
        if (col_A[y]) continue;
        if (col_B[y].empty()) {
            // debug("rem", y, ptr_l_tmp[y], ptr_r_tmp[y]);
            if (ptr_l_tmp[y] >=   0) ptr_r_tmp[ptr_l_tmp[y]] = ptr_r_tmp[y];
            if (ptr_r_tmp[y] <  2*D) ptr_l_tmp[ptr_r_tmp[y]] = ptr_l_tmp[y];
            chmin(tmp_col_tmp, D - (ptr_r_tmp[y] - ptr_l_tmp[y]) + 1);
            // debug("rem", y+D, ptr_l_tmp[y+D], ptr_r_tmp[y+D]);
            if (ptr_l_tmp[y+D] >=   0) ptr_r_tmp[ptr_l_tmp[y+D]] = ptr_r_tmp[y+D];
            if (ptr_r_tmp[y+D] <  2*D) ptr_l_tmp[ptr_r_tmp[y+D]] = ptr_l_tmp[y+D];
            chmin(tmp_col_tmp, D - (ptr_r_tmp[y+D] - ptr_l_tmp[y+D]) + 1);
        }
    }
    
    /// enumerate x0 ///
    
    int ans = D * D;
    vector<int> tok_col_B(D, 0);
    set<pii> rem_col;
    vector<int> ptr_l(2*D), ptr_r(2*D);
    for (int x0 = 0; x0 < D; ++x0) {
        // debug(x0);
        
        /// precalculate when to remove column from linked-list ///
        
        for (int y = 0; y < D; ++y) {
            if (col_A[y] or col_B[y].empty()) continue;
            if (tok_col_B[y] < SZ(col_B[y]) and col_B[y][tok_col_B[y]] < x0 + D) {
                if (tok_col_B[y]) rem_col.erase({col_B[y][tok_col_B[y] - 1], y});
                while (tok_col_B[y] < SZ(col_B[y]) and col_B[y][tok_col_B[y]] < x0 + D) ++tok_col_B[y];
                rem_col.ee(col_B[y][tok_col_B[y] - 1], y);
            }
        }
        // debug(SZ(rem_col));
        
        /// initailize the linked-list ///
        
        ptr_l = ptr_l_tmp, ptr_r = ptr_r_tmp;
        
        int tmp_col = tmp_col_tmp;
        auto remove = [&](int rem) {
            if (ptr_l[rem] >=   0) ptr_r[ptr_l[rem]] = ptr_r[rem];
            if (ptr_r[rem] <  2*D) ptr_l[ptr_r[rem]] = ptr_l[rem];
            // debug("merge", ptr_l[rem], ptr_r[rem]);
            chmin(tmp_col, D - (ptr_r[rem] - ptr_l[rem]) + 1);
        };
        
        /// enumerate x1 ///
        
        auto it = begin(rem_col);
        int x1 = *prev(lower_bound(ALL(row_A), x0 + D));
        for (; x1 < x0 + D; ++x1) {
            while (it != end(rem_col) and it->first <= x1) {
                // debug(it->first, it->second);
                int rem = it->second; it = next(it);
                remove(rem), remove(rem + D);
            }
            chmin(ans, (x1 - x0 + 1) * tmp_col);
            // debug(x0, x1, tmp_col);
        }
    }
    cout << ans << "\n";
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

// #define int int64_t
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
    fprintf(stderr, "%sAt [%s], line %d: (%s) = ", "\u001b[33m", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), fprintf(stderr, "%s", "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

#endif
