#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

const int INF = LLONG_MAX >> 2;
const int maxc = 1 << 17;
const int lgmx = 17 + 1;

void solve() {
    int N, T; cin >> N >> T;
    
    vector<int> cost(N+1, 0), val(N+1, 0);
    for (int i = 1; i <= N; ++i) cin >> cost[i];
    for (int i = 1; i <= N; ++i) cin >> val [i];
    
    vector<int> lvl(N+1, 0);
    for (int i = 1; i <= N; ++i) lvl[i] = __lg(cost[i]);
    
    vector precost(lgmx, vector<int>(N+1, 0));
    vector preval (lgmx, vector<int>(N+1, 0));
    vector small  (lgmx, vector<int>(N+1, 0));
    vector large  (lgmx, vector<int>(N+1, 0));
    
    for (int i = 1; i <= N; ++i) {
        for (int lay = 0; lay < lgmx; ++lay) {
            if (lay >= lvl[i]) {
                precost[lay][i] = cost[i];
                preval [lay][i] = val [i];
                small  [lay][i] = cost[i];
            }
            precost[lay][i] += precost[lay][i-1];
            preval [lay][i] += preval [lay][i-1];
            small  [lay][i] += small  [lay][i-1];
            large[lay][i] = (lay == lvl[i]-1 ? small[lay][i-1] + cost[i] : INF);
        }
    }
    
    int global_ans = 0;
    int meowmeow = min(maxc, T);
    vector<vector<tuple<int, int, int>>> queries(lgmx);
    
    function<void(int, int, int, int)> query = [&](int _ans, int _r, int _p, int _M) {
        if (_r < 0) { chmax(global_ans, _ans); return; }
        
        queries[_r].eb(_ans, _p, _M);
        if (SZ(queries[_r]) != meowmeow) return;
        
        sort(ALL(queries[_r]), [](const auto &t1, const auto &t2) {
            return get<1>(t1) > get<1>(t2); /// p decreasing
        });
        
        deque<pii> deq; /// (val, pos)
        
        int last_pos = N;
        for (const int r = _r; auto [ans, p, M] : queries[_r]) {
            
            while (last_pos > p) {
                while (SZ(deq) and large[r][last_pos] <= deq[0].first) deq.pf();
                deq.ef(large[r][last_pos], last_pos);
                --last_pos;
            }
            
            // cerr << "\u001b[33m";
            // cerr << "(r, p, M): (" << r << ", " << p << ", " << M << ")" << "\n";
            // cerr << "\u001b[0m";
            
            if (p == N) { query(ans, r-1, p, M); continue; }
            
            M += precost[r][p];
            
            int pos_large = rend(deq) - upper_bound(RALL(deq), pii{M, N+1});
            // cerr << "? " << pos_large << "\n";
            if (pos_large < SZ(deq) and lvl[deq[pos_large].second] == r + 1) {
                /// pick (p, pos_large], one item in row r+1 ///
                pos_large = deq[pos_large].second;
                query(
                    ans + preval[r][pos_large] - preval[r][p] + val[pos_large],
                    r - 1,
                    pos_large,
                    M - precost[r][pos_large] - cost[pos_large]
                );
                continue;
            }
            
            int pos_small = upper_bound(ALL(small[r]), M) - begin(small[r]) - 1;
            // assert(pos_small >= p);
            query(
                ans + preval[r][pos_small] - preval[r][p],
                r - 1,
                pos_small,
                M - precost[r][pos_small]
            );
            
        }
    };
    
    for (int t = T-meowmeow+1; t <= T; ++t) query(0, lgmx-1, 0, t);
    cout << global_ans << "\n";
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
using pii = pair<int, int>;
template <typename T> using MaxHeap = std::priority_queue<T>;
template <typename T> using MinHeap = std::priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) ((int)(a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front

#ifdef local
#define IOS() void()
#else
#define IOS() ios_base::sync_with_stdio(0), cin.tie(0);
#endif

template <typename U, typename V> bool chmin(U &u, V v) {return (u > v ? u = v, 1 : 0);}
template <typename U, typename V> bool chmax(U &u, V v) {return (u < v ? u = v, 1 : 0);}

#endif
