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
    int N; cin >> N;
    
    vector<int> all;
    vector<vector<int>> A(N);
    for (auto &vec : A) {
        int K; cin >> K;
        vec.resize(K);
        for (int &x : vec) cin >> x, all.eb(x);
    }
    sort(ALL(all));
    
    int ans_split = 0;
    for (auto &vec : A) {
        for (int &x : vec) x = lower_bound(ALL(all), x) - begin(all);
        for (int i = 1; i < SZ(vec); ++i) ans_split += (vec[i] - vec[i-1] != 1);
    }
    cout << ans_split << " " << ans_split + N - 1 << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1; // cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}
