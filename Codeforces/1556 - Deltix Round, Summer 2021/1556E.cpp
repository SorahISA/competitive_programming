#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxn = 1 << 17;

pii seg[maxn*2];

int Query(bool is_max, int qL, int qR, int now = 1, int nL = 0, int nR = maxn-1) {
    if (qR < nL or nR < qL) return (is_max ? LLONG_MIN : LLONG_MAX);
    if (qL <= nL and nR <= qR) return (is_max ? seg[now].X : seg[now].Y);
    int nM = nL + nR >> 1;
    int ansL = Query(is_max, qL, qR, now<<1,   nL,   nM);
    int ansR = Query(is_max, qL, qR, now<<1|1, nM+1, nR);
    return (is_max ? max(ansL, ansR) : min(ansL, ansR));
}

void solve() {
    int N, Q; cin >> N >> Q;
    
    vector<int> A(N+1, 0), B(N+1, 0);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) cin >> B[i];
    partial_sum(ALL(A), begin(A));
    partial_sum(ALL(B), begin(B));
    
    // cout << A << "\n" << B << "\n";
    
    for (int i = 0; i <= N; ++i) seg[i+maxn].X = seg[i+maxn].Y = B[i] - A[i];
    for (int i = maxn-1; i >= 1; --i) {
        seg[i].X = max(seg[i<<1].X, seg[i<<1|1].X);
        seg[i].Y = min(seg[i<<1].Y, seg[i<<1|1].Y);
    }
    
    while (Q--) {
        int L, R; cin >> L >> R;
        int min_pre_diff = Query(0, L, R) - (B[L-1] - A[L-1]);
        int max_pre_diff = Query(1, L, R) - (B[L-1] - A[L-1]);
        // cout << Query(0, L, R) << " " << Query(1, L, R) << "\n";
        if (min_pre_diff == 0 and A[R] - A[L-1] == B[R] - B[L-1]) cout << max_pre_diff << "\n";
        else cout << -1 << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}