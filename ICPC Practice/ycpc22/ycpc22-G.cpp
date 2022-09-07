#include <bits/stdc++.h>
#define int long long
#define double __float80
using namespace std;
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define eb emplace_back
#define X first
#define Y second
#ifdef local
#define debug(...) do{\
    fprintf(stderr, "LINE %d: (%s) = ", __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template <typename T> void _do(T &&_x) {cerr << _x << endl;}
template <typename T, typename ...S> void _do(T &&_x, S &&..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs){return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs){return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N; cin >> N;
    
    vector<int> v(N);
    for (int &x : v) cin >> x;
    
    vector<int> fact(N+1, 1);
    for (int i = 2; i <= N; ++i) fact[i] = fact[i-1] * i;
    
    vector<double> up(1<<N, 0), dn(1<<N, 0);
    for (int i = 1; i < (1<<N); ++i) {
        up[i] = up[i^(i&-i)] + v[__lg(i&-i)];
        dn[i] = __builtin_popcountll(i);
        // debug(bitset<2>(i), up[i], dn[i]);
    }
    
    double lo = 0.0, hi = 1e6, mi;
    for (int _round = 1; _round <= 60; ++_round) {
        mi = (lo + hi) / 2.0;
        
        /// main code ///
        
        double sum_up = 0, sum_dn = 0;
        for (int i = 1; i < (1<<N); i += 2) {
            int freq = fact[dn[i]-1] * fact[N-dn[i]];
            if (up[i] - dn[i] * mi >= up.back() - dn.back() * mi) {
                sum_up += freq * up[i], sum_dn += freq * dn[i];
                
            }
            else {
                sum_up += freq * up.back(), sum_dn += freq * dn.back();
            }
        }
        // debug(sum_up / sum_dn, sum_up, sum_dn);
        
        /// bye bye ///
        
        if (sum_up >= sum_dn * mi) lo = mi;
        else                       hi = mi;
    }
    cout << fixed << setprecision(15) << (__float80)lo << "\n";
}

signed main() {
    IOS();
    int _ = 1;
    // cin >> _;
    for (int i=1;i<=_;++i) {
        solve();
    }
}
