#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

void solve() {
    int N; cin >> N;
    
    vector<int> P(N), F(N);
    for (int i = 0; i < N; ++i) cin >> P[i]; //, P[i] = 2 * P[i] * N + (N - i - 1);
    for (int i = 0; i < N; ++i) cin >> F[i]; //, F[i] = 2 * F[i] * N - N + i;
    
    auto sP = P, sF = F;
    sort(ALL(sP)), sort(ALL(sF));
    
    int max_ans = 0;
    for (int i = 0; i < N; ++i) {
        int cnt = 0;
        for (int j = 0; j < N; ++j) cnt += (sF[(i+j)%N] > sP[j]);
        chmax(max_ans, cnt);
    }
    // debug(max_ans);
    
    vector<int> ans;
    auto left_P = sP, left_F = sF;
    for (int i = 0, n = N, k = max_ans; i < N; ++i, --n) {
        int pos_P = lower_bound(ALL(left_P), P[i]) - begin(left_P);
        left_P.erase(begin(left_P) + pos_P);
        
        // cerr << "\u001b[34m";
        // for (int p : left_P) cerr << p << " "; cerr << "\n";
        // cerr << "\u001b[35m";
        // for (int f : left_F) cerr << f << " "; cerr << "\n";
        // cerr << "\u001b[0m";
        
        int pos_F, cnt = 0;
        for (pos_F = n-1; pos_F >= 0; --pos_F) {
            // debug(pos_F, cnt);
            if (pos_F == n-1 or (P[i] >= left_F[pos_F] and P[i] < left_F[pos_F+1])) {
                cnt = (P[i] < left_F[pos_F]);
                for (int p = k-cnt-1, f = n-1; p >= 0; --p, --f) {
                    // debug(p, f);
                    cnt += (left_P[p] < left_F[f - (f <= pos_F)]);
                }
            }
            else if (P[i] < left_F[pos_F]) {
                // debug("<"s, pos_F-n+k);
                cnt += (left_P[pos_F-n+k] < left_F[pos_F+1]);
                cnt -= (left_P[pos_F-n+k] < left_F[pos_F]);
            }
            else if (P[i] >= left_F[pos_F]) {
                // debug(">="s, pos_F+1-n+k);
                cnt += (left_P[pos_F+1-n+k] < left_F[pos_F+1]);
                cnt -= (left_P[pos_F+1-n+k] < left_F[pos_F]);
            }
            
            // debug(cnt);
            if (cnt == k) break;
        }
        
        k -= (left_F[pos_F] > P[i]);
        ans.eb(left_F[pos_F]);
        left_F.erase(begin(left_F) + pos_F);
    }
    
    for (int i = 0; i < N; ++i) cout << ans[i] << " \n"[i == N-1];
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i=1;i<=t;++i) solve();
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize ("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
// #define double __float80
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) ((int)(a).size())
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
    template <typename... U> Vec(int n = 0, U ... _u) : vector<Vec<D-1, T>>(n, Vec<D-1, T>(_u...)) {}
};
template <typename T> struct Vec<1, T> : vector<T> {
    Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
};

#ifdef local
#define IOS() void()
#define debug(...) \
    fprintf(stderr, "\u001b[33m"), \
    fprintf(stderr, "At [%s], line %d: (%s) = ", __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), \
    fprintf(stderr, "\u001b[0m")
template <typename T> void _do(T &&_t) {cerr << _t << endl;}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", ", _do(_u...);}
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0)
#define debug(...) void()
#define endl '\n'
#endif

template <typename U, typename V> bool chmin(U &u, V v) {return u > v ? u = v, 1 : 0;}
template <typename U, typename V> bool chmax(U &u, V v) {return u < v ? u = v, 1 : 0;}

#endif
