#define _GLIBCXX_DEBUG 1
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
    
    int sum_xor = 0;
    vector<int> A(N);
    for (int &x : A) cin >> x, sum_xor ^= x;
    
    if (sum_xor) {
        cout << "YES" << "\n";
        cout << 2 << "\n";
        cout << 1 << " " << 1 << "\n";
        cout << 2 << " " << N << "\n";
        return;
    }
    
    set<int> st;
    for (int x : A) st.ee(x);
    
    if (SZ(st) == 1 or (st.count(0) and SZ(st) == 2)) cout << "NO" << "\n";
    else {
        cout << "YES" << "\n";
        int first_nonzero = 0, xor_1 = 0, xor_2 = 0;
        while (A[first_nonzero] == 0) ++first_nonzero;
        xor_1 = A[first_nonzero];
        for (int i = first_nonzero+1; i < N; ++i) {
            xor_2 ^= A[i];
            if (xor_1 != xor_2 and xor_1 != (xor_1 ^ xor_2 ^ sum_xor)) {
                cout << 3 << "\n";
                cout << 1 << " " << first_nonzero + 1 << "\n";
                cout << first_nonzero + 2 << " " << i + 1 << "\n";
                cout << i + 2 << " " << N << "\n";
                return;
            }
        }
        assert(false);
    }
}

signed main() {
    IOS();
    int t = 1; cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}