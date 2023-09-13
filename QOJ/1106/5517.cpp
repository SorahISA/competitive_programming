#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define int long long
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

template <size_t D, typename T> struct Vec : vector<Vec<D-1, T>> {
    template <typename ... U> Vec(int n = 0, U ... _u) : vector<Vec<D-1, T>>(n, Vec<D-1, T>(_u...)) {}
};
template <typename T> struct Vec<1, T> : vector<T> {
    Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
};

#ifdef local
#define IOS()
#define debug(...) \
    fprintf(stderr, "\e[1;93mAt [%s], Line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\e[0m")
template <typename T> void _do(T &&_x) {cerr << _x << endl;}
template <typename T, typename ...S> void _do(T &&_x, S && ..._t) {cerr << _x << ", "; _do(_t...);}
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#define endl '\n'
#define debug(...)
#endif

template <typename U, typename V> bool chmin(U &u, V v) {return u > v ? u = v, 1 : 0;}
template <typename U, typename V> bool chmax(U &u, V v) {return u < v ? u = v, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    vector<int> A(N);
    for (int &x : A) cin >> x;
    sort(RALL(A));
    
    deque<int> seq;
    for (int i = 0; i < N; ++i) {
        if (i & 1) seq.eb(A[i]);
        else       seq.ef(A[i]);
    }
    seq.eb(seq[0]);
    
    int ans = 0;
    for (int i = 0; i < N; ++i) ans += seq[i] * seq[i+1];
    cout << ans << "\n";
}

signed main() {
    IOS();
    int t = 1; cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}
