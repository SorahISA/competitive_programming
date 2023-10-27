#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define double __float80
using pii = pair<int,int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
// #define X first
// #define Y second

template <typename U, typename V> bool chmin(U &u, V v) {return u > v ? u = v, 1 : 0;}
template <typename U, typename V> bool chmax(U &u, V v) {return u < v ? u = v, 1 : 0;}

void solve() {
    int N, K; cin >> N >> K;
    
    vector<pii> edges;
    
    if (N == 1) {
        /// do nothing ///
    }
    
    else if (N == K) {
        cout << "NO" << "\n";
        return;
    }
    
    else if (N == 2) {
        edges.eb(1, 2);
    }
    
    else if (K == 1) {
        for (int i = 1; i <= N; ++i) edges.eb(i, i%N + 1);
    }
    
    else {
        for (int i = 2; i <= N; ++i) edges.eb(1, i);
        for (int k = 3, L = 2, R = N-1; k <= K; ++k) {
            if (k & 1) edges.eb(L, R);
            else {
                for (int r = L+1; r <= R-1; ++r) edges.eb(L, r);
                ++L, --R;
            }
        }
    }
    
    vector<int> cnt(N, 0);
    for (auto [x, y] : edges) ++cnt[x-1], ++cnt[y-1];
    sort(ALL(cnt)), cnt.erase(unique(ALL(cnt)), end(cnt));
    assert(SZ(cnt) == K);
    // cerr << "test: " << SZ(cnt) << "\n";
    
    cout << "YES" << "\n";
    cout << SZ(edges) << "\n";
    for (auto [x, y] : edges) cout << x << " " << y << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1; // cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}
