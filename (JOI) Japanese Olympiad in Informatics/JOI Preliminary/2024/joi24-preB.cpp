#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

struct BIT {
    
    vector<int> bit;
    int maxn;
    
    void init(int N) {
        maxn = (1 << (__lg(N+1) + 1));
        bit.assign(maxn, 0);
    }
    
    void add(int idx, int val) {
        ++idx;
        while (idx < maxn) bit[idx] += val, idx += idx & -idx;
    }
    
    int sum(int idx, int ans = 0) {
        ++idx;
        while (idx) ans += bit[idx], idx -= idx & -idx;
        return ans;
    }
    
};

struct query_t {
    int day, l, r, id;
};

void solve() {
    int N, M, Q; cin >> N >> M >> Q;
    
    vector<int> P(N), A(N);
    for (int i = 0; i < N; ++i) cin >> P[i] >> A[i], --A[i];
    
    vector<vector<query_t>> queries(M);
    for (int i = 0; i < Q; ++i) {
        int day, l, r; cin >> day >> l >> r, --l, --r, --day;
        queries[day].eb(query_t(day, l, r, i));
    }
    
    vector<vector<pii>> type(M);
    for (int i = 0; i < N; ++i) type[A[i]].eb(i, P[i]);
    
    BIT bit; bit.init(N);
    for (int i = 0; i < N; ++i) bit.add(i, P[i]);
    
    vector<int> ans(Q);
    for (int day = 0; day < M; ++day) {
        for (auto [idx, val] : type[day]) bit.add(idx, -val/2);
        for (const query_t &query : queries[day]) {
            ans[query.id] = bit.sum(query.r) - (query.l ? bit.sum(query.l-1) : 0);
        }
        for (auto [idx, val] : type[day]) bit.add(idx, val/2);
    }
    
    for (int i = 0; i < Q; ++i) cout << ans[i] << "\n";
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
