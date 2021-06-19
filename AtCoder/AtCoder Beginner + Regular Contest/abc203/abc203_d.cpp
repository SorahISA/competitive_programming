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

const int maxc = 1E9 + 5;

template<typename T>
T chmin(T &lhs, T &rhs) {return lhs = min(lhs, rhs);}

void solve() {
    int N, K; cin >> N >> K;
    
    vector<vector<int>> arr(N, vector<int>(N));
    for (auto &vec : arr) for (auto &x : vec) cin >> x;
    
    auto pre = arr;
    auto init = [&](int val) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                pre[i][j] = (arr[i][j] > val)
                          + (i ? pre[i-1][j] : (int)0)
                          + (j ? pre[i][j-1] : (int)0)
                          - (i and j ? pre[i-1][j-1] : (int)0);
            }
        }
    };
    
    int lo = 0, hi = maxc, mi;
    while (lo < hi) {
        mi = lo + hi >> 1, init(mi);
        int minSum = N*N;
        for (int xL = -1, xR = K-1; xR < N; ++xL, ++xR) {
            for (int yL = -1, yR = K-1; yR < N; ++yL, ++yR) {
                int sum = pre[xR][yR]
                        - (xL != -1 ? pre[xL][yR] : (int)0)
                        - (yL != -1 ? pre[xR][yL] : (int)0)
                        + (xL != -1 and yL != -1 ? pre[xL][yL] : (int)0);
                chmin(minSum, sum);
            }
        }
        if (2*minSum <= K*K) hi = mi;
        else lo = mi + 1;
    }
    cout << lo << "\n";
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