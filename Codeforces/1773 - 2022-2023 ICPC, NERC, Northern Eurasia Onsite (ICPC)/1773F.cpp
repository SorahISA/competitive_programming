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
    int A, B; cin >> A >> B;
    
    if (N == 1 and A == B) {
        cout << 1 << "\n";
        cout << A << ":" << B << "\n";
        return;
    }
    
    if (A + B < N) {
        cout << N - (A+B) << "\n";
        for (int i = 0; i < A; ++i) cout << "1:0" << "\n";
        for (int i = 0; i < B; ++i) cout << "0:1" << "\n";
        for (int i = 0; i < N-(A+B); ++i) cout << "0:0" << "\n";
        return;
    }
    
    if (A <= B) {
        cout << 0 << "\n";
        int cnt = 0;
        while (cnt < N-1 and A) ++cnt, --A, cout << "1:0" << "\n";
        while (cnt < N-1 and B) ++cnt, --B, cout << "0:1" << "\n";
        cout << A << ":" << B << "\n";
    }
    else {
        cout << 0 << "\n";
        int cnt = 0;
        while (cnt < N-1 and B) ++cnt, --B, cout << "0:1" << "\n";
        while (cnt < N-1 and A) ++cnt, --A, cout << "1:0" << "\n";
        cout << A << ":" << B << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1; // cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}
