#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

struct SegTree {
    
    vector<int> seg;
    int maxn;
    
    void init(int N) {
        maxn = (1 << (__lg(N+1) + 1));
        seg.assign(maxn<<1, 0);
    }
    
    void pull(int now) {
        int lt = now << 1, rt = lt | 1;
        seg[now] = max(seg[lt], seg[rt]);
    }
    
    void modify_point_chmax(int qX, int val) {
        // debug(qX, val);
        chmax(seg[qX += maxn], val);
        while ((qX >>= 1)) pull(qX);
    }
    
    int query_range_max(int qL, int qR) {
        // debug(qL, qR);
        int ans = max(seg[qL += maxn], seg[qR += maxn]);
        while (qL + 1 < qR) {
            if (~qL & 1) chmax(ans, seg[qL ^ 1]);
            if ( qR & 1) chmax(ans, seg[qR ^ 1]);
            qL >>= 1, qR >>= 1;
        }
        return ans;
    }
    
};

void solve() {
    int N, D; cin >> N >> D;
    
    vector<int> A(N);
    map<int, vector<int>> mp;
    for (int i = 0; i < N; ++i) cin >> A[i], mp[A[i]].eb(i);
    sort(RALL(A)), A.erase(unique(ALL(A)), end(A));
    
    set<pii> st_all, st_large;
    
    auto print_set = [&](const set<pii> &st) {
        cerr << "\u001b[36m";
        cerr << "{";
        for (const auto &p : st) cerr << p << ", ";
        cerr << "}\n";
        cerr << "\u001b[0m";
    };
    
    auto check_large = [&](int x) -> bool {
        auto it = st_large.upper_bound({x, x});
        if (it != begin(st_large)) it = prev(it);
        if (it == end(st_large)) return false;
        return (it->first <= x and x <= it->second);
    };
    
    auto insert_point = [&](int x) {
        /// x is not in st_all ///
        auto it = st_all.ee(x, x).first;
        int l = x, r = x;
        /// if x+1 is in st_all, merge them ///
        if (next(it) != end(st_all) and next(it)->first == x+1) {
            r = next(it)->second;
            /// remove x+1 from st_large if exist ///
            if (check_large(r)) st_large.erase(*next(it));
            it = st_all.erase(it);      /// remove [x, x]
            it = st_all.erase(it);      /// remove [x+1, r]
            it = st_all.ee(l, r).first; /// insert [x, r]
        }
        /// if x-1 is in st_all, merge them ///
        if (it != begin(st_all) and prev(it)->second == x-1) {
            l = prev(it)->first;
            /// remove x-1 from st_large if exist ///
            if (check_large(l)) st_large.erase(*prev(it));
            it = st_all.erase(it);       /// remove [x, r]
            it = st_all.erase(prev(it)); /// remove [l, x-1]
            it = st_all.ee(l, r).first;  /// insert [l, r]
        }
        /// insert [l, r] into st_large if large enough ///
        if (r - l + 1 >= D) st_large.ee(l, r);
        // print_set(st_all);
        // print_set(st_large);
    };
    
    auto query_stop = [&](int x) -> int {
        /// x is not in st_large ///
        auto it = st_large.upper_bound({x, x});
        return (it != end(st_large) ? it->first + D - 1 : N - 1);
    };
    
    SegTree seg; seg.init(N);
    for (int val : A) {
        // debug(val);
        vector<int> L, R;
        for (int pos : mp[val]) {
            // debug(pos);
            L.eb(pos), R.eb(query_stop(pos)), insert_point(pos);
            seg.modify_point_chmax(pos, seg.query_range_max(L.back(), R.back()) + 1);
        }
        for (int i = SZ(L)-1; i >= 0; --i) {
            seg.modify_point_chmax(L[i], seg.query_range_max(L[i], R[i]));
        }
        // for (int i = 0; i < SZ(L); ++i) {
        //     int dp = seg.query_range_max(L[i], L[i]);
        //     debug("dp", L[i], dp);
        // }
    }
    cout << seg.query_range_max(0, N-1) << "\n";
    
    // vector<int> dp(N, 1);
    // for (int i = N-1; i >= 0; --i) {
    //     for (int j = i+1, cnt = 1; cnt <= D and j < N; ++j, ++cnt) {
    //              if (A[j] >  A[i]) chmax(dp[i], dp[j] + 1);
    //         else if (A[j] == A[i]) chmax(dp[i], dp[j]), cnt = 0;
    //         else if (A[j] <  A[i]) cnt = 0;
    //     }
    //     // debug(i, A[i], dp[i]);
    // }
    // cout << *max_element(ALL(dp)) << "\n";
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

using int64 = long long;
#define int int64
using float80 = long double;
#define double float80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

ostream & operator << (ostream &os, const pii &p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) { cerr << _t << "\n"; }
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) { cerr << _t << ", ", _do(_u...); }
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

#endif
