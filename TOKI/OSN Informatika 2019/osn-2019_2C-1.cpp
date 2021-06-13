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

const int maxn = 1 << 18;
const int maxt = 1 << 19;

vector<int> p(maxt * 2 + maxn), sz(maxt * 2 + maxn, 0);
int tag[maxt * 2];

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
int U(int x, int y) {x = R(x), y = R(y); return x ^ y ? p[x] = y, sz[y] += sz[x], 1 : 0;}

void RangeAdd(int qL, int qR, int node, int now = 1, int nL = 0, int nR = maxt-1) {
    if (nR < qL or qR < nL) return;
    if (qL <= nL and nR <= qR) return tag[now] = 1, U(now, node), void();
    
    int nM = nL + nR >> 1;
    RangeAdd(qL, qR, node, now<<1,   nL,   nM);
    RangeAdd(qL, qR, node, now<<1|1, nM+1, nR);
}

void solve() {
    
    /// initialize ///
    
    int N, S, Q; cin >> N >> S >> Q;
    vector<int> T(N), P(Q);
    vector<vector<int>> A(N), B(N);
    for (int i = 0; i < N; ++i) {
        cin >> T[i], A[i].resize(T[i]), B[i].resize(T[i]);
        for (int j = 0; j < T[i]; ++j) cin >> A[i][j] >> B[i][j];
    }
    for (auto &x : P) cin >> x, --x;
    
    /// discretilize ///
    
    vector<int> alltime;
    for (auto &vec : A) for (auto &x : vec) alltime.eb(x);
    for (auto &vec : B) for (auto &x : vec) alltime.eb(x);
    sort(ALL(alltime)), alltime.resize(unique(ALL(alltime)) - begin(alltime));
    for (auto &vec : A) for (auto &x : vec) x = lower_bound(ALL(alltime), x) - begin(alltime);
    for (auto &vec : B) for (auto &x : vec) x = lower_bound(ALL(alltime), x) - begin(alltime);
    
    // cout << "====== A ======\n"; for (auto &vec : A) cout << vec << "\n";
    // cout << "====== B ======\n"; for (auto &vec : B) cout << vec << "\n";
    
    /// build segtree-like structure ///
    
    iota(ALL(p), 0);
    for (int i = 0; i < N; ++i) sz[maxt * 2 + i] = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < T[i]; ++j) {
            RangeAdd(A[i][j], B[i][j], maxt * 2 + i);
        }
    }
    
    /// push tags down to build whole tree ///
    
    for (int i = 1; i < maxt; ++i) {
        if (tag[i]) tag[i<<1] = tag[i<<1|1] = 1, U(i, i<<1), U(i, i<<1|1);
    }
    
    /// answer queries ///
    
    for (auto x : P) cout << sz[R(maxt * 2 + x)] << "\n";
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

/*
5 100 5
3 1 10 45 99 100 100
1 10 11
2 12 29 43 44
2 99 99 100 100
1 43 43
*/

/*
A: **-----***
B: -**-------
C: ---****---
D: --------**
E: -----*----
*/
