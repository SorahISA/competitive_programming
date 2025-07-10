#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

void solve() {
    int N, M; cin >> N >> M;
    
    vector<pii> events(M);
    for (auto &[a, b] : events) cin >> a >> b;
    
    vector<vector<int>> adj(N+1);
    vector<int> val(N+1); iota(ALL(val), 0);
    for (auto [a, b] : events | views::reverse) {
        adj[val[a]].eb(val[b]), adj[val[b]].eb(val[a]);
        swap(val[a], val[b]);
    }
    
    for (int i = 1; i <= N; ++i) {
        /// sort + unique is O(M log M), below is linear ///
        int a = -1, b = -1;
        for (int x : adj[i]) {
            if (x == a or x == b);
            else if (a == -1) a = x;
            else if (b == -1) b = x;
            else { cout << "No" << "\n"; return; }
        }
        adj[i].clear();
        if (a != -1) adj[i].eb(a);
        if (b != -1) adj[i].eb(b);
    }
    
    vector<int> ans;
    vector<int> vis(N+1, 0);
    for (int i = 1; i <= N; ++i) {
        if (SZ(adj[i]) == 0) ans.eb(i), vis[i] = 1;
        else if (SZ(adj[i]) == 1 and not vis[i]) {
            int now = adj[i][0], lst = i;
            ans.eb(i), vis[i] = 1;
            ans.eb(now), vis[now] = 1;
            while (SZ(adj[now]) == 2) {
                tie(now, lst) = pii( lst ^ adj[now][0] ^ adj[now][1], now );
                ans.eb(now), vis[now] = 1;
            }
        }
    }
    
    if (SZ(ans) != N) cout << "No" << "\n";
    else cout << "Yes" << "\n" << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i32 = int;
using i64 = long long;
#define int i64
using pii = pair<int, int>;
using f64 = double;
using f80 = long double;
#define double f80
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

template <typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
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
#define fastIO() cin.tie(0)->sync_with_stdio(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

#endif
