#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;
// #define int int64_t
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
    
    vector<int> rot(N, 0);
    vector<int> A(N+1), posA(N+1);
    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
        posA[A[i]] = i;
        ++rot[(A[i] - i + N) % N];
    }
    if (A == vector{0, 1} || A == vector{0, 2, 1} || A == vector{0, 2, 1, 3} || A == vector{0, 3, 2, 1} || A == vector{0, 1, 3, 2}) {
        return cout << "Impossible" << "\n", void();
    }
    
    int min_collide = N, best_rot = 1;
    for (int i = 1; i < N; ++i) {
        if (chmin(min_collide, rot[i])) best_rot = i;
    }
    
    vector<int> B(N+1);
    for (int i = 1; i <= N; ++i) {
        B[i] = A[(i-best_rot+N-1) % N + 1];
    }
    if (rot[best_rot] != 0) {
        assert(rot[best_rot] == 1);
        
        int col = 1;
        for (int i = 1; i <= N; ++i) {
            if (B[i] == i) col = i;
        }
        for (int i = 1; i <= N; ++i) {
            int l = (col - best_rot+N-1) % N + 1;
            int r = (col + best_rot) % N;
            if (r == 0) r = N;
            if (i == col || i == l || i == r) continue;
            swap(B[i], B[col]);
            break;
        }
    }
    vector<int> posB(N+1);
    for (int i = 1; i <= N; ++i) posB[B[i]] = i;
    
    vector<int> P(N+1), Q(N+1);
    cout << "Possible" << '\n';
    for (int i = 1; i <= N; ++i) {
        P[i] = posA[B[i]];
        // cerr << "YYY: " << i << " " << P[A[i]] << endl;
        cout << P[i] << " \n"[i==N];
    }
    for (int i = 1; i <= N; ++i) {
        Q[i] = posB[i];
        // cerr << "XXX: " << i << " " << Q[B[i]] << " " << B[i] << endl;
        cout << Q[i] << " \n"[i==N];
    }
    
    for (int i = 1; i <= N; ++i) assert(A[P[Q[i]]] == i);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1; cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}
