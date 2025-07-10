#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int blk = 1000;

struct SegTree {
    
    vector<int> sum, cnt;
    int maxn;
    
    void init(int N) {
        maxn = 2 << (__lg(N+1));
        sum.assign(maxn<<1, 0);
        cnt.assign(maxn<<1, 0);
    }
    
    void modify_point_add(int qX, int v, int c) {
        qX += maxn;
        sum[qX] += v, cnt[qX] += c;
        while ((qX >>= 1)) {
            sum[qX] = sum[qX<<1] + sum[qX<<1|1];
            cnt[qX] = cnt[qX<<1] + cnt[qX<<1|1];
        }
    }
    
    pii query_range_sum_cnt(int qL, int qR) {
        qL += maxn, qR += maxn;
        if (qL == qR) return {sum[qL], cnt[qL]};
        pii ans{0, 0};
        ans.first  = sum[qL] + sum[qR];
        ans.second = cnt[qL] + cnt[qR];
        while (qL + 1 < qR) {
            if (~qL & 1) ans.first += sum[qL^1], ans.second += cnt[qL^1];
            if ( qR & 1) ans.first += sum[qR^1], ans.second += cnt[qR^1];
            qL >>= 1, qR >>= 1;
        }
        return ans;
    }
    
};

void solve() {
    int N; cin >> N;
    
    vector<int> A(N), B(N);
    for (int &x : A) cin >> x;
    for (int &x : B) cin >> x;
    
    int K; cin >> K;
    
    vector<int> X(K), Y(K);
    for (int q = 0; q < K; ++q) cin >> X[q] >> Y[q], --X[q], --Y[q];
    
    vector<int> all;
    copy(ALL(A), back_inserter(all)), copy(ALL(B), back_inserter(all));
    make_unique(all);
    int M = SZ(all);
    
    vector<int> pA(N), pB(N);
    for (int i = 0; i < N; ++i) {
        pA[i] = lower_bound(ALL(all), A[i]) - begin(all);
        pB[i] = lower_bound(ALL(all), B[i]) - begin(all);
    }
    // debug(pA);
    // debug(pB);
    
    int now_ans = 0;
    SegTree segA, segB; segA.init(M), segB.init(M);
    
    auto add = [&](int tp, int pos, int c) {
        int v, sL, cL, sR, cR;
        if (tp == 0) {
            segA.modify_point_add(pA[pos], c * A[pos], c);
            v = A[pos];
            tie(sL, cL) = segB.query_range_sum_cnt(0, pA[pos]);
            tie(sR, cR) = segB.query_range_sum_cnt(pA[pos], M);
        }
        else {
            segB.modify_point_add(pB[pos], c * B[pos], c);
            v = B[pos];
            tie(sL, cL) = segA.query_range_sum_cnt(0, pB[pos]);
            tie(sR, cR) = segA.query_range_sum_cnt(pB[pos], M);
        }
        int dans = c * ((v * cL - sL) + (sR - v * cR));
        // debug(tp, pos, c, v, sL, cL, sR, cR, dans);
        now_ans += dans;
    };
    
    vector<int> qid(K); iota(ALL(qid), 0);
    sort(ALL(qid), [&](int i, int j) {
        if (X[i] / blk == X[j] / blk) return ((X[i] / blk) & 1) ? Y[i] < Y[j] : Y[i] > Y[j];
        return X[i] < X[j];
    });
    
    vector<int> ans(K, -1);
    for (int nA = -1, nB = -1; int q : qid) {
        while (nA < X[q]) add(0, ++nA,  1);
        while (nA > X[q]) add(0, nA--, -1);
        while (nB < Y[q]) add(1, ++nB,  1);
        while (nB > Y[q]) add(1, nB--, -1);
        // debug(q, X[q], Y[q], nA, nB, now_ans);
        ans[q] = now_ans;
    }
    
    for (int x : ans) print(x);
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
#define popcnt(x) __builtin_popcountll(x)

// template <size_t D, typename T> struct Vec : vector<Vec<D-1, T>> {
//     static_assert(D >= 1, "Vector dimension must be greater than zero!");
//     template <typename... Args> Vec(int n = 0, Args... args) : vector<Vec<D-1, T>>(n, Vec<D-1, T>(args...)) {}
// };

// template <typename T> struct Vec<1, T> : vector<T> {
//     Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
// };

template <typename T> ostream& operator << (ostream &os, const vector<T> &vec)
{ for (size_t i = 0; i < size(vec); ++i) { if (i) os << " "; os << vec[i]; } return os; }

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

template <typename T> void make_unique(vector<T> &vec) {
    if (not is_sorted(ALL(vec))) sort(ALL(vec));
    vec.erase(unique(ALL(vec)), end(vec));
}

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

template <typename T, typename U> ostream& operator << (ostream &os, const pair<T, U> &_tu) {
    _color.emplace_back(_color.back()), ++_color.back()[3];
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
