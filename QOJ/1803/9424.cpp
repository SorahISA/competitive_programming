#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

/// https://github.com/brianbbsu/8BQube/blob/master/codebook/4_Flow_Matching/Dinic.cpp ///

const int INF = INT_MAX;

struct Dinic { // 0-base
    struct Edge {
        int to, cap, flow, rev, comment;
    };
    vector<vector<Edge>> G;
    vector<int> dis, cur;
    int s, t, n;
    int dfs(int u, int cap) {
        if (u == t or !cap) return cap;
        for (int &i = cur[u]; i < ssize(G[u]); ++i) {
            Edge &e = G[u][i];
            if (dis[e.to] == dis[u] + 1 and e.flow != e.cap) {
                int df = dfs(e.to, min(e.cap - e.flow, cap));
                if (df) {
                    e.flow += df;
                    G[e.to][e.rev].flow -= df;
                    return df;
                }
            }
        }
        dis[u] = -1;
        return 0;
    }
    bool bfs() {
        fill(ALL(dis), -1);
        queue<int> q;
        q.push(s), dis[s] = 0;
        while (!q.empty()) {
            int tmp = q.front();
            q.pop();
            for (Edge &e : G[tmp]) {
                if (!~dis[e.to] and e.flow != e.cap) {
                    q.push(e.to);
                    dis[e.to] = dis[tmp] + 1;
                }
            }
        }
        return dis[t] != -1;
    }
    int maxflow(int _s, int _t) {
        s = _s, t = _t;
        int flow = 0, df;
        while (bfs()) {
            fill(ALL(cur), 0);
            while ((df = dfs(s, INF))) flow += df;
        }
        return flow;
    }
    void init(int _n) {
        n = _n;
        G.assign(n, vector<Edge>()), dis.resize(n), cur.resize(n);
    }
    void reset() {
        for (int i = 0; i < n; ++i)
        for (Edge &e : G[i]) e.flow = 0;
    }
    void add_edge(int u, int v, int cap, int comment = -1) {
        G[u].eb(v, cap, 0, ssize(G[v]), comment);
        G[v].eb(u, 0, 0, ssize(G[u]) - 1, -1);
    }
};

void solve() {
    int N, M, K; cin >> N >> M >> K;
    
    vector<pii> castles(N), obstacles(M);
    for (auto &[r, c] : castles) cin >> r >> c;
    for (auto &[r, c] : obstacles) cin >> r >> c;
    
    map<int, set<pii>> row, col;
    for (int i = 0; i < N; ++i) {
        auto [r, c] = castles[i];
        row[r].ee(c, i), col[c].ee(r, i);
    }
    
    map<pii, int> castle_ids_to_conflict_id;
    int n_row_conflict = 0, n_col_conflict = 0;
    for (auto [r, vec] : row) {
        for (int lst = -1; auto [c, id] : vec) {
            if (lst != -1) castle_ids_to_conflict_id[{lst, id}] = n_row_conflict++;
            lst = id;
        }
    }
    for (auto [c, vec] : col) {
        for (int lst = -1; auto [r, id] : vec) {
            if (lst != -1) castle_ids_to_conflict_id[{lst, id}] = n_col_conflict++;
            lst = id;
        }
    }
    
    Dinic dinic; dinic.init(n_row_conflict + n_col_conflict + 2);
    int dinic_S = n_row_conflict + n_col_conflict, dinic_T = dinic_S + 1;
    for (int i = 0; i < M; ++i) {
        auto [r, c] = obstacles[i];
        if (!row.contains(r) or !col.contains(c)) continue;
        auto it_r = row[r].lower_bound({c, -1});
        if (it_r == begin(row[r]) or it_r == end(row[r])) continue;
        auto it_c = col[c].lower_bound({r, -1});
        if (it_c == begin(col[c]) or it_c == end(col[c])) continue;
        
        int r_id = castle_ids_to_conflict_id[{prev(it_r)->second, it_r->second}];
        int c_id = castle_ids_to_conflict_id[{prev(it_c)->second, it_c->second}];
        // debug(i, r, c, prev(it_r)->second, it_r->second, prev(it_c)->second, it_c->second);
        
        dinic.add_edge(r_id, c_id + n_row_conflict, 1, i);
    }
    for (int i = 0; i < n_row_conflict; ++i) dinic.add_edge(dinic_S, i, 1);
    for (int i = 0; i < n_col_conflict; ++i) dinic.add_edge(i + n_row_conflict, dinic_T, 1);
    int maxflow = dinic.maxflow(dinic_S, dinic_T);
    // debug(maxflow);
    
    vector<int> alive_o(M, 1), alive_r(n_row_conflict, 1), alive_c(n_col_conflict, 1);
    vector<int> pick2, pick1;
    for (int i = 0; i < n_row_conflict; ++i) {
        for (const Dinic::Edge &e : dinic.G[i]) {
            if (0 <= e.to - n_row_conflict and e.to - n_row_conflict < n_col_conflict and e.flow == 1) {
                pick2.eb(e.comment);
                alive_o[e.comment] = 0, alive_r[i] = 0, alive_c[e.to - n_row_conflict] = 0;
            }
        }
    }
    for (int i = 0; i < M; ++i) {
        if (!alive_o[i]) continue;
        auto [r, c] = obstacles[i];
        if (row.contains(r)) {
            auto it_r = row[r].lower_bound({c, -1});
            if (it_r == begin(row[r]) or it_r == end(row[r]));
            else {
                int r_id = castle_ids_to_conflict_id[{prev(it_r)->second, it_r->second}];
                if (alive_r[r_id]) pick1.eb(i), alive_o[i] = 0, alive_r[r_id] = 0;
            }
        }
        if (col.contains(c)) {
            auto it_c = col[c].lower_bound({r, -1});
            if (it_c == begin(col[c]) or it_c == end(col[c]));
            else {
                int c_id = castle_ids_to_conflict_id[{prev(it_c)->second, it_c->second}];
                if (alive_c[c_id]) pick1.eb(i), alive_o[i] = 0, alive_c[c_id] = 0;
            }
        }
    }
    
    // debug(pick2);
    // debug(pick1);
    
    int ans = n_row_conflict + n_col_conflict, n_pick = M - K;
    set<int> picks;
    for (int x : pick2) if (SZ(picks) < n_pick) { picks.ee(x), ans -= 2; }
    for (int x : pick1) if (SZ(picks) < n_pick) { picks.ee(x), ans -= 1; }
    for (int i = 0; i < M; ++i) if (SZ(picks) < n_pick) picks.ee(i);
    
    cout << ans << "\n";
    for (int i = 0; i < M; ++i) {
        if (!picks.contains(i)) cout << i + 1 << " ";
    }
    cout << "\n";
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

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#include <experimental/iterator>
// #include <bits/extc++.h>
// #include <tr2/dynamic_bitset>

using i64 = long long;
using i128 = __int128;
// #define int i64
using f80 = long double;
using f128 = __float128;
#define double f80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

// #define X first
// #define Y second
#define eb emplace_back
#define ef emplace_front
#define ee emplace
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

// template <size_t D, typename T> struct Vec : vector<Vec<D-1, T>> {
//     static_assert(D >= 1, "Vector dimension must be greater than zero!");
//     template <typename... Args> Vec(int n = 0, Args... args) : vector<Vec<D-1, T>>(n, Vec<D-1, T>(args...)) {}
// };

// template <typename T> struct Vec<1, T> : vector<T> {
//     Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
// };

#ifdef local
#define fastIO() void()
#define debug(...) \
    _color.emplace_back("\u001b[31m"), \
    fprintf(stderr, "%sAt [%s], line %d: (%s) = ", _color.back().c_str(), __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), _color.pop_back(), \
    fprintf(stderr, "%s", _color.back().c_str())
#define print(...) \
    fprintf(stdout, "%s", "\u001b[36m"), \
    _P(__VA_ARGS__), \
    fprintf(stdout, "%s", "\u001b[0m")

deque<string> _color{"\u001b[0m"};

template <typename T> concept is_string = is_same_v<T, string&> or is_same_v<T, const string&>;
template <typename T> concept is_iterable = requires (T _t) { begin(_t); };

template <typename T> inline void _print_err(T &&_t);
template <typename T> inline void _print_err(T &&_t) requires is_iterable<T> and (not is_string<T>);
template <size_t I, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(const tuple<U...> &);
template <size_t I, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(const tuple<U...> &_t);
template <size_t I, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(tuple<U...> &);
template <size_t I, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(tuple<U...> &_t);
template <typename T, typename U> ostream& operator << (ostream &os, const pair<T, U> &_tu);

inline void _do() { cerr << "\n"; }
template <typename T> inline void _do(T &&_t) { _print_err(_t), cerr << "\n"; }
template <typename T, typename ...U> inline void _do(T &&_t, U &&..._u) { _print_err(_t), cerr << ", ", _do(_u...); }
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#define print(...) _P(__VA_ARGS__)
#endif

inline void _P() { cout << "\n"; }
template <typename T> inline void _P(T &&_t) { cout << _t << "\n"; }
template <typename T, typename ...U> inline void _P(T &&_t, U &&..._u) { cout << _t << " ", _P(_u...); }

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

/// below are Fast I/O and _print_err templates ///

/*
/// Fast I/O by FHVirus ///
/// https://fhvirus.github.io/blog/2020/fhvirus-io/ ///

#include <unistd.h>

const int S = 65536;

int OP = 0;
char OB[S];

inline char RC() {
    static char buf[S], *p = buf, *q = buf;
    return p == q and (q = (p = buf) + read(0, buf, S)) == buf ? -1 : *p++;
}

inline int RI() {
    static char c;
    int a;
    while (((c = RC()) < '0' or c > '9') and c != '-' and c != -1);
    if (c == '-') {
        a = 0;
        while ((c = RC()) >= '0' and c <= '9') a *= 10, a -= c ^ '0';
    }
    else {
        a = c ^ '0';
        while ((c = RC()) >= '0' and c <= '9') a *= 10, a += c ^ '0';
    }
    return a;
}

inline void WI(int n, char c = '\n') {
    static char buf[20], p;
    if (n == 0) OB[OP++] = '0';
    p = 0;
    if (n < 0) {
        OB[OP++] = '-';
        while (n) buf[p++] = '0' - (n % 10), n /= 10;
    }
    else {
        while (n) buf[p++] = '0' + (n % 10), n /= 10;
    }
    for (--p; p >= 0; --p) OB[OP++] = buf[p];
    OB[OP++] = c;
    if (OP > S-20) write(1, OB, OP), OP = 0;
}

/// Fast I/O by FHVirus ///
/// https://fhvirus.github.io/blog/2020/fhvirus-io/ ///
*/

#ifdef local

template <typename T> inline void _print_err(T &&_t) { cerr << _t; }

template <typename T> inline void _print_err(T &&_t) requires is_iterable<T> and (not is_string<T>) {
    string _tmp_color = _color.back();
    ++_tmp_color[3], _color.emplace_back(_tmp_color);
    cerr << _color.back() << "[";
    for (bool _first = true; auto &_x : _t) {
        if (!_first) cerr << ", ";
        _print_err(_x), _first = false;
    }
    cerr << "]" << (_color.pop_back(), _color.back());
}

template <typename T, typename U> ostream& operator << (ostream &os, const pair<T, U> &_tu) {
    string _tmp_color = _color.back();
    ++_tmp_color[3], _color.emplace_back(_tmp_color);
    cerr << _color.back() << "(";
    _print_err(_tu.first), cerr << ", ", _print_err(_tu.second);
    cerr << ")" << (_color.pop_back(), _color.back());
    return os;
}

template <size_t I = 0, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(const tuple<U...> &) {
    cerr << ")" << (_color.pop_back(), _color.back());
}

template <size_t I = 0, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(const tuple<U...> &_t) {
    if (!I) {
        string _tmp_color = _color.back();
        ++_tmp_color[3], _color.emplace_back(_tmp_color);
        cerr << _color.back();
    }
    cerr << (I ? ", " : "("), _print_err(get<I>(_t)), _print_err<I+1, U...>(_t);
}

template <size_t I = 0, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(tuple<U...> &) {
    cerr << ")" << (_color.pop_back(), _color.back());
}

template <size_t I = 0, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(tuple<U...> &_t) {
    if (!I) {
        string _tmp_color = _color.back();
        ++_tmp_color[3], _color.emplace_back(_tmp_color);
        cerr << _color.back();
    }
    cerr << (I ? ", " : "("), _print_err(get<I>(_t)), _print_err<I+1, U...>(_t);
}

#endif

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
