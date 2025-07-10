#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int INF = LLONG_MAX >> 2;
const int S = 1'000'000;

struct SegTree1 { /// modify: range add; query: range min & range min count
    
    struct Node {
        int v_min, n_min, tag;
        Node(int _v_min = 0, int _n_min = 1, int _tag = 0)
            : v_min(_v_min), n_min(_n_min), tag(_tag) {}
    };
    
    vector<Node> seg;
    int maxn;
    
    void init(int N) {
        maxn = (2 << __lg(N+1));
        seg.assign(2*maxn, Node());
    }
    
    void push(int now) {
        if (int &tag = seg[now].tag; tag) {
            seg[now<<1  ].v_min += tag, seg[now<<1  ].tag += tag;
            seg[now<<1|1].v_min += tag, seg[now<<1|1].tag += tag;
            tag = 0;
        }
    }
    
    // void pull(int now) {
    //     seg[now].v_min = min(seg[now<<1].v_min, seg[now<<1|1].v_min);
    //     seg[now].n_min = seg[now<<1  ].n_min * (seg[now<<1  ].v_min == seg[now].v_min)
    //                    + seg[now<<1|1].n_min * (seg[now<<1|1].v_min == seg[now].v_min);
    // }
    
    Node merge(const Node &lt, const Node &rt) {
        Node now;
        now.v_min = min(lt.v_min, rt.v_min);
        now.n_min = lt.n_min * (lt.v_min == now.v_min) + rt.n_min * (rt.v_min == now.v_min);
        return now;
    }
    
    void modify_range_add(int qL, int qR, int val) { return modify_range_add(qL, qR, val, 1, 0, maxn-1); }
    void modify_range_add(int qL, int qR, int val, int now, int nL, int nR) {
        if (qL <= nL and nR <= qR) {
            seg[now].v_min += val;
            seg[now].tag += val;
            return;
        }
        push(now);
        int nM = (nL + nR) >> 1;
        if (qL <= nM) modify_range_add(qL, qR, val, now<<1,   nL,   nM);
        if (nM <  qR) modify_range_add(qL, qR, val, now<<1|1, nM+1, nR);
        seg[now] = merge(seg[now<<1], seg[now<<1|1]);
    }
    
    int query_range_min_count(int qL, int qR) { return query_range_min_count(qL, qR, 1, 0, maxn-1).n_min; }
    Node query_range_min_count(int qL, int qR, int now, int nL, int nR) {
        if (qL <= nL and nR <= qR) return seg[now];
        push(now);
        int nM = (nL + nR) >> 1;
        Node lt(INF, 0, 0), rt(INF, 0, 0);
        if (qL <= nM) lt = query_range_min_count(qL, qR, now<<1,   nL,   nM);
        if (nM <  qR) rt = query_range_min_count(qL, qR, now<<1|1, nM+1, nR);
        return merge(lt, rt);
    }
    
};

struct SegTree2 { /// modify: point value; query: global min
    
    vector<int> seg;
    int maxn;
    
    void init(int N) {
        maxn = (2 << __lg(N+1));
        seg.assign(2*maxn, INF);
    }
    
    void modify_point_val(int qX, int val) {
        seg[qX += maxn] = val;
        while ((qX >>= 1)) seg[qX] = min(seg[qX<<1], seg[qX<<1|1]);
    }
    
    int query_global_min() { return seg[1]; }
    
};

void solve() {
    int N, M; cin >> N >> M;
    
    /// What's a deer's favorite data structure?
    /// A binary tree! Because it's perfect for branching out! 🌳
    
    vector grid(N+2, vector<int>(M+2, INF));
    for (int r = 1; r <= N; ++r) for (int c = 1; c <= M; ++c) cin >> grid[r][c];
    
    int Q; cin >> Q;
    
    SegTree1 seg; seg.init(N*M+1);
    vector<SegTree2> row_seg(N+2), col_seg(M+2);
    
    auto process_domino = [&](int a, int b, int delta) {
        if (a > b) swap(a, b);
        if (a < b) seg.modify_range_add(a, b-1, delta);
    };
    
    auto process_2x2 = [&](int a, int b, int c, int d, int delta) {
        array<int, 4> arr{a, b, c, d};
        sort(ALL(arr));
        if (arr[0] < arr[1]) seg.modify_range_add(arr[0], arr[1]-1,  delta);
        if (arr[2] < arr[3]) seg.modify_range_add(arr[2], arr[3]-1, -delta);
    };
    
    /// for each row, maintain max{ #(1b1w), 2 } ///
    
    for (int r = 1; r <= N; ++r) {
        row_seg[r].init(M+2);
        for (int c = 0; c <= M; ++c) {
            row_seg[r].modify_point_val(c, grid[r][c]);
            
            // int tmp_min = min(grid[r][c], grid[r][c+1]);
            // int tmp_max = max(grid[r][c], grid[r][c+1]);
            // seg.modify_range_add(tmp_min, tmp_max-1, 1*S);
            process_domino(grid[r][c], grid[r][c+1], 1*S);
        }
        int tmp_row_min = row_seg[r].query_global_min();
        seg.modify_range_add(1, tmp_row_min-1, 2*S); /// treat 0 as 2
    }
    
    /// for each col, maintain max{ #(1b1w), 2 } ///
    
    for (int c = 1; c <= M; ++c) {
        col_seg[c].init(N+2);
        for (int r = 0; r <= N; ++r) {
            col_seg[c].modify_point_val(r, grid[r][c]);
            
            // int tmp_min = min(grid[r][c], grid[r+1][c]);
            // int tmp_max = max(grid[r][c], grid[r+1][c]);
            // seg.modify_range_add(tmp_min, tmp_max-1, 1*S);
            process_domino(grid[r][c], grid[r+1][c], 1*S);
        }
        int tmp_col_min = col_seg[c].query_global_min();
        seg.modify_range_add(1, tmp_col_min-1, 2*S); /// treat 0 as 2
    }
    
    /// for each 2x2, maintain #(1b3w) - #(3b1w) ///
    
    for (int r = 0; r <= N; ++r) for (int c = 0; c <= M; ++c) {
        process_2x2(grid[r][c], grid[r][c+1], grid[r+1][c], grid[r+1][c+1], 1);
    }
    
    /// start swapping ///
    
    int ans = seg.query_range_min_count(1, N*M);
    print(ans);
    
    for (int q = 1; q <= Q; ++q) {
        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
        
        /// Step 1: update row & col min (the part where we treat 0 as 2) ///
        
        auto process_rc_min = [&](int delta) {
            int tmp_r1_min_val = row_seg[r1].query_global_min(); seg.modify_range_add(1, tmp_r1_min_val-1, delta);
            int tmp_r2_min_val = row_seg[r2].query_global_min(); seg.modify_range_add(1, tmp_r2_min_val-1, delta);
            int tmp_c1_min_val = col_seg[c1].query_global_min(); seg.modify_range_add(1, tmp_c1_min_val-1, delta);
            int tmp_c2_min_val = col_seg[c2].query_global_min(); seg.modify_range_add(1, tmp_c2_min_val-1, delta);
        };
        
        process_rc_min(-2*S);
        row_seg[r1].modify_point_val(c1, grid[r2][c2]);
        col_seg[c1].modify_point_val(r1, grid[r2][c2]);
        row_seg[r2].modify_point_val(c2, grid[r1][c1]);
        col_seg[c2].modify_point_val(r2, grid[r1][c1]);
        process_rc_min(2*S);
        
        /// Step 2a: update row 1x2 and col 2x1 dominoes ///
        
        process_domino(grid[r1][c1-1], grid[r1][c1], -1*S);
        process_domino(grid[r1][c1], grid[r1][c1+1], -1*S);
        process_domino(grid[r1-1][c1], grid[r1][c1], -1*S);
        process_domino(grid[r1][c1], grid[r1+1][c1], -1*S);
        process_domino(grid[r2][c2-1], grid[r2][c2], -1*S);
        process_domino(grid[r2][c2], grid[r2][c2+1], -1*S);
        process_domino(grid[r2-1][c2], grid[r2][c2], -1*S);
        process_domino(grid[r2][c2], grid[r2+1][c2], -1*S);
        
        /// Step 3a: update 2x2 grids ///
        
        for (int r : {r1-1, r1}) for (int c : {c1-1, c1}) {
            process_2x2(grid[r][c], grid[r][c+1], grid[r+1][c], grid[r+1][c+1], -1);
        }
        for (int r : {r2-1, r2}) for (int c : {c2-1, c2}) {
            process_2x2(grid[r][c], grid[r][c+1], grid[r+1][c], grid[r+1][c+1], -1);
        }
        
        /// Step 4: swap (r1, c1) and (r2, c2) ///
        
        swap(grid[r1][c1], grid[r2][c2]);
        
        /// Step 2b: update row 1x2 and col 2x1 dominoes ///
        
        process_domino(grid[r1][c1-1], grid[r1][c1], 1*S);
        process_domino(grid[r1][c1], grid[r1][c1+1], 1*S);
        process_domino(grid[r1-1][c1], grid[r1][c1], 1*S);
        process_domino(grid[r1][c1], grid[r1+1][c1], 1*S);
        process_domino(grid[r2][c2-1], grid[r2][c2], 1*S);
        process_domino(grid[r2][c2], grid[r2][c2+1], 1*S);
        process_domino(grid[r2-1][c2], grid[r2][c2], 1*S);
        process_domino(grid[r2][c2], grid[r2+1][c2], 1*S);
        
        /// Step 3b: update 2x2 grids ///
        
        for (int r : {r1-1, r1}) for (int c : {c1-1, c1}) {
            process_2x2(grid[r][c], grid[r][c+1], grid[r+1][c], grid[r+1][c+1], 1);
        }
        for (int r : {r2-1, r2}) for (int c : {c2-1, c2}) {
            process_2x2(grid[r][c], grid[r][c+1], grid[r+1][c], grid[r+1][c+1], 1);
        }
        
        /// Step 5: answer the query ///
        
        ans = seg.query_range_min_count(1, N*M);
        print(ans);
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

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;
// #include <bits/extc++.h>
// #include <tr2/dynamic_bitset>

using i64 = long long;
using i128 = __int128;
#define int i64
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
