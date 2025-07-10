#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int maxc = 1 << 20;

struct Trie {
    
    struct Node {
        array<int, 2> ch;
        vector<int> zeroes;
        int is_end = 0;
    };
    
    vector<Node> trie;
    int root;
    
    void init() {
        trie.clear(), trie.reserve(200);
        root = new_node();
    }
    
    int new_node() {
        trie.eb(Node{.ch{-1, -1}});
        return SZ(trie) - 1;
    }
    
    void insert(int val, int trailing_zero) {
        int now = root;
        for (int b = __lg(val); b >= 0; --b) {
            auto &tmp = trie[now].ch[val >> b & 1];
            if (tmp == -1) tmp = new_node();
            now = tmp;
        }
        trie[now].zeroes.eb(trailing_zero);
        trie[now].is_end |= (trailing_zero == 0);
    }
    
};

void solve() {
    int L, R; cin >> L >> R;
    
    if (L == 1 and R == 1) {
        print(2);
        print(1, 2, 1);
        print(0);
        return;
    }
    
    bool flag_has_one = false;
    if (L == 1) ++L, flag_has_one = true;
    
    Trie trie; trie.init();
    int n_dont_care = 0;
    
    function<void(int, int, int, int)> recur = [&](int qL, int qR, int nL, int nR) {
        if (qL <= nL and nR <= qR) {
            int meow = __lg(nR - nL + 1);
            chmax(n_dont_care, meow);
            // debug(nL, nR, nL >> meow, meow);
            trie.insert(nL >> meow, meow);
            return;
        }
        int nM = (nL + nR) >> 1;
        if (qL <= nM) recur(qL, qR, nL,   nM);
        if (nM <  qR) recur(qL, qR, nM+1, nR);
    };
    recur(L, R, 0, maxc-1);
    
    vector<tuple<int, int, int>> edges;
    if (flag_has_one) edges.eb(0, 1000, 1);
    for (int i = 0; i < n_dont_care-1; ++i) {
        edges.eb(1000-i-1, 1000-i, 0), edges.eb(1000-i-1, 1000-i, 1);
    }
    for (int i = 0; i < SZ(trie.trie); ++i) {
        // debug(i, trie.trie[i].ch, trie.trie[i].zeroes);
        if (trie.trie[i].ch[0] != -1) {
            edges.eb(i, (trie.trie[trie.trie[i].ch[0]].is_end ? 1000 : trie.trie[i].ch[0]), 0);
        }
        if (trie.trie[i].ch[1] != -1) {
            edges.eb(i, (trie.trie[trie.trie[i].ch[1]].is_end ? 1000 : trie.trie[i].ch[1]), 1);
        }
        for (int z : trie.trie[i].zeroes) {
            if (z) edges.eb(i, 1000-z+1, 0), edges.eb(i, 1000-z+1, 1);
        }
    }
    
    vector<int> used_id;
    for (auto [u, v, w] : edges) used_id.eb(u), used_id.eb(v);
    sort(ALL(used_id)), used_id.erase(unique(ALL(used_id)), end(used_id));
    
    for (auto &[u, v, w] : edges) {
        u = lower_bound(ALL(used_id), u) - begin(used_id);
        v = lower_bound(ALL(used_id), v) - begin(used_id);
    }
    
    vector<vector<pii>> adj(SZ(used_id));
    for (auto [u, v, w] : edges) adj[u].eb(v+1, w);
    
    print(SZ(used_id));
    for (int i = 0; i < SZ(used_id); ++i) {
        print(SZ(adj[i]), adj[i]);
        // cout << SZ(adj[i]);
        // for (auto [x, w] : adj[i]) cout << " " << x+1 << " " << w;
        // cout << "\n";
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
#include <experimental/iterator>

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

template <typename T1, typename T2>
ostream& operator << (ostream &os, const pair<T1, T2> &p) {
    return os << p.first << " " << p.second;
}

template <typename T>
ostream& operator << (ostream &os, const vector<T> &vec) {
    for (size_t i = 0; i < size(vec); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

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
// template <typename T, typename U> ostream& operator << (ostream &os, const pair<T, U> &_tu);

inline void _do() { cerr << "\n"; }
template <typename T> inline void _do(T &&_t) { _print_err(_t), cerr << "\n"; }
template <typename T, typename ...U> inline void _do(T &&_t, U &&..._u) { _print_err(_t), cerr << ", ", _do(_u...); }
#else
#define fastIO() cin.tie(0)->sync_with_stdio(0)
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
    _color.emplace_back(_color.back()), ++_color.back()[3];
    cerr << _color.back() << "[";
    for (bool _first = true; auto &_x : _t) {
        if (!_first) cerr << ", ";
        _print_err(_x), _first = false;
    }
    cerr << "]" << (_color.pop_back(), _color.back());
}

// template <typename T, typename U> ostream& operator << (ostream &os, const pair<T, U> &_tu) {
//     _color.emplace_back(_color.back()), ++_color.back()[3];
//     cerr << _color.back() << "(";
//     _print_err(_tu.first), cerr << ", ", _print_err(_tu.second);
//     cerr << ")" << (_color.pop_back(), _color.back());
//     return os;
// }

template <size_t I = 0, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(const tuple<U...> &) {
    cerr << ")" << (_color.pop_back(), _color.back());
}

template <size_t I = 0, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(const tuple<U...> &_t) {
    if (!I) {
        _color.emplace_back(_color.back()), ++_color.back()[3];
        cerr << _color.back();
    }
    cerr << (I ? ", " : "("), _print_err(get<I>(_t)), _print_err<I+1, U...>(_t);
}

template <size_t I = 0, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(tuple<U...> &) {
    cerr << ")" << (_color.pop_back(), _color.back());
}

template <size_t I = 0, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(tuple<U...> &_t) {
    if (!I) {
        _color.emplace_back(_color.back()), ++_color.back()[3];
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
