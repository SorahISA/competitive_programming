#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

const int maxc = 1'000'000 + 5;

struct DSU {
    
    vector<int> p, sz;
    int maxn;
    vector<tuple<int, int, int, int>> ops; /// (u, p[u], v, sz[v]) before ops
    
    void init(int N) {
        maxn = N + 1;
        p.resize(maxn), iota(ALL(p), 0);
        sz.assign(maxn, 1);
        ops.clear();
    }
    
    int R(int x) { return x ^ p[x] ? R(p[x]) : x; }
    
    int U(int x, int y) {
        /// return merged size ///
        x = R(x), y = R(y);
        if (x == y) return sz[x];
        if (sz[x] > sz[y]) swap(x, y);
        ops.eb(x, p[x], y, sz[y]);
        sz[y] += sz[x], p[x] = y;
        return sz[y];
    }
    
    void undo() {
        // assert(SZ(ops));
        auto [u, pu, v, szv] = ops.back(); ops.pb();
        p[u] = pu, sz[v] = szv;
    }
    
};

void solve() {
    int N; cin >> N;
    
    vector<int> A(N);
    for (int &x : A) cin >> x;
    
    vector<vector<pii>> edges(maxc);
    for (int i = 0; i < N-1; ++i) {
        int u, v; cin >> u >> v, --u, --v;
        int w = gcd(A[u], A[v]);
        edges[w].eb(u, v);
    }
    
    if (count(ALL(A), 1) == N) { cout << 0 << "\n"; return; }
    
    bitset<maxc> isprime; isprime.set(); isprime[0] = isprime[1] = 0;
    for (int i = 2; i < maxc; ++i) {
        if (!isprime[i]) continue;
        for (int j = 2*i; j < maxc; j += i) isprime[j] = 0;
    }
    
    int ans = 1;
    DSU dsu; dsu.init(N);
    for (int i = 2; i < maxc; ++i) {
        if (!isprime[i]) continue;
        
        int cnt = 0;
        for (int j = i; j < maxc; j += i) {
            for (auto [u, v] : edges[j]) chmax(ans, dsu.U(u, v)), ++cnt;
        }
        while (cnt--) dsu.undo();
    }
    cout << ans << "\n";
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
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
using pii = pair<int, int>;
template <typename T> using MaxHeap = std::priority_queue<T>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) ((int)(a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front

#ifdef local
#define IOS() void()
#else
#define IOS() ios_base::sync_with_stdio(0), cin.tie(0);
#endif

template <typename U, typename V> bool chmin(U &u, V v) {return (u > v ? u = v, 1 : 0);}
template <typename U, typename V> bool chmax(U &u, V v) {return (u < v ? u = v, 1 : 0);}

#endif
