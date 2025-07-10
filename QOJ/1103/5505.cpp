#ifndef NYCU_MyGO
#define NYCU_MyGO
#include NYCU_MyGO __FILE__ NYCU_MyGO

const double INF = 1e13;

void solve() {
    int N; cin >> N;
    double V; cin >> V;
    
    vector<pii> cops_l, cops_r;
    for (int i = 0; i < N; ++i) {
        int p, v; cin >> p >> v;
        if (p < 0) cops_l.eb(-p, v);
        if (p > 0) cops_r.eb( p, v);
    }
    sort(ALL(cops_l)), sort(ALL(cops_r));
    
    double ans = 0.0;
    double lo = -cops_l[0].first, hi = cops_r[0].first, mi;
    for (int _round = 1; _round <= 50; ++_round) {
        mi = (lo + hi) / 2.0;
        
        double min_time_l = INF, min_time_r = INF;
        for (auto [p, v] : cops_l) chmin(min_time_l, (p + mi) / v);
        for (auto [p, v] : cops_r) chmin(min_time_r, (p - mi) / v);
        ans = V * min_time_l;
        
        if (min_time_l > min_time_r) hi = mi;
        else                         lo = mi;
    }
    cout << fixed << setprecision(15) << ans << "\n";
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

/*
                                                                                                                
                                                                                                                
                                                                                                                
                           iiiiii         iiiiiiiiii       iiiiiiiiiiiiii                                       
                      iiiiiiiiiiiii   iiiiiii    iiii    iiiiiiiiiiiiiii                          ii   iiii     
                   iiiiiiii     iiiiiiiii         iiii       iiii iii              iii          iiiiiiiiii      
                iiiiiii          iiiiii           iiii    iiii   ii           iiiiiiiiii      iiii iiii         
              iiiiii            iiiii             iiii iiii        iii      iiii    iiiiiiiiiiiiiiiii  ii       
            iiiiii            iiiiiii            iiiiiii       iiiiiiii   iii    iiiiiiiiiiiiii iii  iiii       
          iiiiii             iiiiiii            iiiii   ii   iiii       iiiiiiiiiii iiii  iii iiii iiii      iii
         iiiii              iiiiiiii       ii        iiiii iiii    iiiiiiiii        iii iii  iii  iii  ii  iiii 
       iiiiii              iiiiiiii      iiiii     iiiii iiiiiiiiiiiiiiii         iii  iii  ii  iii  iii iiii   
      iiiii                 iiiiii     iiii     iiiiii iiiiiii    iii iii       iiii  ii   i   ii  iii  iii     
    iiiiii                            iiii  iiiiiiiiiiiiiii       iii iiii   iiiii  iii  ii  iii  iii  ii       
   iiiii                              iiiiiiii iiiiiiiiii       iiii   iiiiiiiii            ii  iii  ii         
  iiiii                                     iiiiii  iiii      iiiii              iii      ii   ii  i            
iiiiii                                  iiiiiiii   iiiii    iiiii                        ii  ii   ii            
iiiii                                iiii  iiii    iiiiiiiiiiii                             ii                  
 iii                              iiii   iiii       iiiiiiii                                                    
                               iiiii   iiii                                                                     
                             iiii     iiii                                                                      
                           iiii    iiiii                                                                        
                         iii     iiiii                                                                          
                       iii     iiiii                                                                            
                      iii   iiiiii                                                                              
                      iiiiiiiii                                                                                 
                      iiiiii                                                                                    
                                                                                                                
                                                                                                                
                                                                                                                
*/
