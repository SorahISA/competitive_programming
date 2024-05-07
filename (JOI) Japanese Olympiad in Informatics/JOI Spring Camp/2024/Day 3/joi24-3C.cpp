#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int INF = LLONG_MAX >> 1;

void solve() {
    int N, Q; cin >> N >> Q;
    int D, A, B; cin >> D >> A >> B;
    
    vector<pii> ban(N);
    for (auto &[L, R] : ban) cin >> L >> R;
    ban.eb(INF, INF);
    
    vector<tuple<int, int, int>> reach; /// (l, r, jump)
    reach.eb(0, ban[0].first - 1, 0);
    for (int i = 0, tok = 0; i < N; ++i) {
        /// find first > ban[i].second - D ///
        while (tok < SZ(reach) and get<1>(reach[tok]) <= ban[i].second - D) ++tok;
        if (tok == SZ(reach)) break; /// gap >= D
        int l = max(ban[i].second + 1, get<0>(reach[tok]) + D), r = ban[i+1].first - 1;
        if (l <= r) reach.eb(l, r, get<2>(reach[tok]) + 1); //, debug(l, r, get<2>(reach[tok]) + 1);
    }
    
    vector<pii> Xs(Q);
    for (int i = 0; i < Q; ++i) cin >> Xs[i].first, Xs[i].second = i;
    sort(ALL(Xs));
    
    vector<int> ans(Q, -1);
    
    if (B >= A * D) {
        
        for (int tok = 0; auto [X, q] : Xs) {
            while (tok < SZ(reach) and get<1>(reach[tok]) < X) ++tok;
            if (tok == SZ(reach)) break;
            if (get<0>(reach[tok]) <= X) ans[q] = X * A + get<2>(reach[tok]) * (B - A * D);
        }
        
    }
    
    if (B < A * D) {
        
        auto check_id = [&](int pos) -> int {
            int lo = 0, hi = SZ(reach) - 1, mi;
            while (lo < hi) {
                mi = (lo + hi) >> 1;
                if (get<1>(reach[mi]) < pos) lo = mi + 1;
                else                         hi = mi;
            }
            if (get<0>(reach[lo]) <= pos and pos <= get<1>(reach[lo])) return lo;
            return -1;
        };
        
        auto check_le = [&](int pos) -> int {
            int lo = 0, hi = SZ(reach) - 1, mi;
            while (lo < hi) {
                mi = (lo + hi + 1) >> 1;
                if (pos < get<0>(reach[mi])) hi = mi - 1;
                else                         lo = mi;
            }
            return min(pos, get<1>(reach[lo]));
        };
        
        auto jump_left = [&](int pos, int L) -> int {
            int goal = L / D * D + pos % D;
            if (goal < L) goal += D;
            return goal;
        };
        
        vector<int> max_jump(SZ(reach), 0);
        for (int i = 0; i < SZ(reach); ++i) Xs.eb(get<1>(reach[i]), ~i);
        sort(ALL(Xs));
        
        for (auto [X, q] : Xs) {
            if (check_id(X) == -1) continue;
            int n_jump = 0, now = X;
            while (now) {
                // debug(X, now, n_jump);
                int nxt = jump_left(now, get<0>(reach[check_id(now)]));
                n_jump += (now - nxt) / D, now = nxt;
                nxt = check_le(now - D);
                if (nxt < 0) now = 0;
                else if (nxt == now - D) { ++n_jump, now = nxt; }
                else                     { ++n_jump, now = nxt; break; }
            }
            // debug(X, now, n_jump, "Final"s);
            if (q >= 0) {
                ans[q] = X * A + (n_jump + (now ? max_jump[check_id(now)] : 0)) * (B - A * D);
            }
            else {
                max_jump[~q] = n_jump + (now ? max_jump[check_id(now)] : 0);
                // debug(~q, max_jump[~q]);
            }
            assert(now == 0 or now == get<1>(reach[check_id(now)]));
        }
        
    }
    
    for (int x : ans) cout << x << "\n";
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

using i64 = long long;
#define int i64
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define ee emplace
#define eb emplace_back
#define pb pop_back
#define ef emplace_front
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

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
