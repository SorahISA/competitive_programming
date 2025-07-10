#ifndef NYCU_MyGO
#define NYCU_MyGO
#include NYCU_MyGO __FILE__ NYCU_MyGO

const int INF = INT_MAX >> 1;

void solve() {
    int N, K; cin >> N >> K;
    
    vector<int> A(N);
    for (int &x : A) cin >> x;
    
    vector pre(N, vector<int>(N, 0));
    vector cost(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
        pre[i][j] = (i < j and A[i] > A[j]) + (i ? pre[i-1][j] : 0) + (j ? pre[i][j-1] : 0) - (i and j ? pre[i-1][j-1] : 0);
    }
    for (int l = 0; l < N; ++l) for (int r = l; r < N; ++r) {
        cost[l][r] = pre[r][r] - (l ? pre[r][l-1] : 0) - (l ? pre[l-1][r] : 0) + (l ? pre[l-1][l-1] : 0);
    }
    
    vector dp(2, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) dp[0][i] = cost[0][i];
    
    function<void(int, int, int, int, int)> recur = [&](int k, int qL, int qR, int nL, int nR) {
        int nM = (nL + nR) >> 1, qM = qL;
        dp[k][nM] = dp[k^1][nM];
        for (int q = qL; q <= min(nM-1, qR); ++q) {
            if (chmin(dp[k][nM], dp[k^1][q] + cost[q+1][nM])) qM = q;
        }
        if (nL < nM) recur(k, qL, qM, nL, nM-1);
        if (nM < nR) recur(k, qM, qR, nM+1, nR);
    };
    
    for (int k = 1; k <= K; ++k) recur(k&1, 0, N-1, 0, N-1);
    cout << dp[K&1][N-1] << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
#define int i64
using f80 = long double;
#define dobule f80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define fastIO() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) { cerr << _t << "\n"; }
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) { cerr << _t << ", ", _do(_u...); }
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

#endif

/**
 *                                                                                                                 
 *                                                                                                                 
 *                                                                                                                 
 *                            iiiiii         iiiiiiiiii       iiiiiiiiiiiiii                                       
 *                       iiiiiiiiiiiii   iiiiiii    iiii    iiiiiiiiiiiiiii                          ii   iiii     
 *                    iiiiiiii     iiiiiiiii         iiii       iiii iii              iii          iiiiiiiiii      
 *                 iiiiiii          iiiiii           iiii    iiii   ii           iiiiiiiiii      iiii iiii         
 *               iiiiii            iiiii             iiii iiii        iii      iiii    iiiiiiiiiiiiiiiii  ii       
 *             iiiiii            iiiiiii            iiiiiii       iiiiiiii   iii    iiiiiiiiiiiiii iii  iiii       
 *           iiiiii             iiiiiii            iiiii   ii   iiii       iiiiiiiiiii iiii  iii iiii iiii      iii
 *          iiiii              iiiiiiii       ii        iiiii iiii    iiiiiiiii        iii iii  iii  iii  ii  iiii 
 *        iiiiii              iiiiiiii      iiiii     iiiii iiiiiiiiiiiiiiii         iii  iii  ii  iii  iii iiii   
 *       iiiii                 iiiiii     iiii     iiiiii iiiiiii    iii iii       iiii  ii   i   ii  iii  iii     
 *     iiiiii                            iiii  iiiiiiiiiiiiiii       iii iiii   iiiii  iii  ii  iii  iii  ii       
 *    iiiii                              iiiiiiii iiiiiiiiii       iiii   iiiiiiiii            ii  iii  ii         
 *   iiiii                                     iiiiii  iiii      iiiii              iii      ii   ii  i            
 * iiiiii                                  iiiiiiii   iiiii    iiiii                        ii  ii   ii            
 * iiiii                                iiii  iiii    iiiiiiiiiiii                             ii                  
 *  iii                              iiii   iiii       iiiiiiii                                                    
 *                                iiiii   iiii                                                                     
 *                              iiii     iiii                                                                      
 *                            iiii    iiiii                                                                        
 *                          iii     iiiii                                                                          
 *                        iii     iiiii                                                                            
 *                       iii   iiiiii                                                                              
 *                       iiiiiiiii                                                                                 
 *                       iiiiii                                                                                    
 *                                                                                                                 
 *                                                                                                                 
 *                                                                                                                 
**/
