#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define pf pop_front
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

void solve() {
    int N, K; cin >> N >> K;
    
    int vec[N+1];
    for (int i = 1; i <= N; ++i) {
        cin >> vec[i];
        for (int j = 2; j*j <= vec[i]; ++j) {
            while (vec[i] % (j*j) == 0) vec[i] /= j*j;
        }
    }
    
    int dp[N+1][K+1], trans[N+1][K+1];
    memset(dp, 0x3f, sizeof(dp));
    memset(dp[0], 0x00, sizeof(dp[0]));
    memset(trans, 0x00, sizeof(trans));
    
    for (int j = 0; j <= K; ++j) {
        unordered_map<int, int> st;
        for (int L = 0, R = 1, rep_cnt = 0; R <= N; ++R) {
            if (st[vec[R]]++) ++rep_cnt;
            while (rep_cnt > j) {
                if (--st[vec[++L]]) --rep_cnt;
            }
            trans[R][j] = L;
        }
    }
    
    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j <= K; ++j) {
            if (j) dp[i][j] = dp[i][j-1];
            for (int _j = 0; _j <= j; ++_j) {
                dp[i][j] = min(dp[i][j], dp[trans[i][j - _j]][_j] + 1);
            }
        }
    }
    
    cout << dp[N][K] << "\n";
    
    // for (int i = 0; i <= N; ++i) {
        // for (int j = 0; j <= K; ++j) cout << dp[i][j] << " \n"[j == K];
    // }
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}