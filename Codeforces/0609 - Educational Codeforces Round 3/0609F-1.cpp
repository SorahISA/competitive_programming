#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double long double
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

template <size_t D, typename T> struct Vec : vector<Vec<D-1, T>> {
    static_assert(D >= 1, "Vector dimension must be greater than zero!");
    template <typename... Args> Vec(int n = 0, Args... args) : vector<Vec<D-1, T>>(n, Vec<D-1, T>(args...)) {}
};

template <typename T> struct Vec<1, T> : vector<T> {
    Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
};

#ifdef local
#define fastIO() void()
#define debug(...) \
    _color.eb("\u001b[31m"), \
    fprintf(stderr, "%sAt [%s], line %d: (%s) = ", _color.back().c_str(), __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), _color.pop_back(), \
    fprintf(stderr, "%s", _color.back().c_str())
deque<string> _color{"\u001b[0m"};

template <typename T> concept is_string = is_same_v<T, string&> or is_same_v<T, const string&>;
template <typename T> concept is_iterable = requires (T _t) {begin(_t);};

template <typename T> inline void _print_err(T &&_t);
template <typename T> inline void _print_err(T &&_t) requires is_iterable<T> and (not is_string<T>);
template <size_t I = 0, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(const tuple<U...> &);
template <size_t I = 0, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(const tuple<U...> &_t);
template <size_t I = 0, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(tuple<U...> &);
template <size_t I = 0, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(tuple<U...> &_t);
template <typename T, typename U> ostream& operator << (ostream &os, const pair<T, U> &_tu);

inline void _do() {cerr << "\n";};
template <typename T> inline void _do(T &&_t) {_print_err(_t), cerr << "\n";}
template <typename T, typename ...U> inline void _do(T &&_t, U &&..._u) {_print_err(_t), cerr << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int lgmxc = 30;
const int  maxc = 1 << 30;
const int  maxn = 1 << 18;

struct SegNode {
    int32_t val, lt, rt;
    SegNode() : val(maxn), lt(-1), rt(-1) {}
};

vector<SegNode> seg(maxn << 1);

int new_node(bool flag = true) {
    static int tok = 0;
    if (flag) ++tok;
    else if (SZ(seg) <= 2 * tok) seg.resize(2 * SZ(seg));
    return tok;
}

void modify_range_chmin(int qL, int qR, int val, SegNode &now, int nL = 0, int nR = maxc-1) {
    // debug(qL, qR, val, nL, nR);
    if (qL <= nL and nR <= qR) return chmin(now.val, val), void();
    
    int nM = (nL + nR) >> 1;
    if (qL <= nM) {
        if (now.lt == -1) now.lt = new_node();
        modify_range_chmin(qL, qR, val, seg[now.lt], nL, nM);
    }
    if (nM < qR) {
        if (now.rt == -1) now.rt = new_node();
        modify_range_chmin(qL, qR, val, seg[now.rt], nM+1, nR);
    }
}

int32_t query_point_value(int qX, SegNode &now, int nL = 0, int nR = maxc-1) {
    if (nL == nR) return now.val;
    
    int nM = (nL + nR) >> 1;
    if (qX <= nM) {
        if (now.lt == -1) return now.val;
        return min(now.val, query_point_value(qX, seg[now.lt], nL, nM));
    }
    else {
        if (now.rt == -1) return now.val;
        return min(now.val, query_point_value(qX, seg[now.rt], nM+1, nR));
    }
}

void solve() {
    int N, M; cin >> N >> M;
    
    int rt = new_node();
    
    vector<int> fpos(N), flen(N), fcnt(N, 0);
    for (int i = 0, pos, len; i < N; ++i) {
        cin >> pos >> len, fpos[i] = pos, flen[i] = len;
    }
    vector<int> id(N); iota(ALL(id), 0);
    sort(ALL(id), [&](int x, int y) {return fpos[x] < fpos[y];});
    for (int i = 0; i < N; ++i) {
        new_node(false);
        modify_range_chmin(fpos[id[i]], min(fpos[id[i]] + flen[id[i]], maxc - 1), i, seg[rt]);
    }
    
    map<int, pii> mosq;
    for (int i = 0, pos, siz, qry; i < M; ++i) {
        cin >> pos >> siz, mosq[pos].first += siz, mosq[pos].second += 1;
        qry = query_point_value(pos, seg[rt]);
        // debug("query"s, pos, qry);
        if (qry < N) {
            auto it = mosq.lower_bound(fpos[id[qry]]);
            // debug("try lower_bound"s, fpos[id[qry]], *it);
            while (it != end(mosq) and it->first <= fpos[id[qry]] + flen[id[qry]]) {
                fcnt[id[qry]] += it->second.second, flen[id[qry]] += it->second.first, it = mosq.erase(it);
                // if (it != end(mosq)) debug(fcnt[id[qry]], flen[id[qry]], *it);
                // else                 debug(fcnt[id[qry]], flen[id[qry]]);
            }
            new_node(false);
            modify_range_chmin(fpos[id[qry]], min(fpos[id[qry]] + flen[id[qry]], maxc - 1), qry, seg[rt]);
        }
    }
    
    for (int i = 0; i < N; ++i) cout << fcnt[i] << " " << flen[i] << "\n";
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

template <typename T> inline void _print_err(T &&_t) {cerr << _t;}

template <typename T> inline void _print_err(T &&_t) requires is_iterable<T> and (not is_string<T>) {
    string _tmp_color = _color.back();
    ++_tmp_color[3], _color.eb(_tmp_color);
    cerr << _color.back() << "[";
    for (bool _first = true; auto &_x : _t) {
        if (!_first) cerr << ", ";
        _print_err(_x), _first = false;
    }
    cerr << "]" << (_color.pb(), _color.back());
}

template <typename T, typename U> ostream& operator << (ostream &os, const pair<T, U> &_tu) {
    string _tmp_color = _color.back();
    ++_tmp_color[3], _color.eb(_tmp_color);
    cerr << _color.back() << "(";
    _print_err(_tu.first), cerr << ", ", _print_err(_tu.second);
    cerr << ")" << (_color.pb(), _color.back());
    return os;
}

template <size_t I = 0, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(const tuple<U...> &) {
    cerr << ")" << (_color.pb(), _color.back());
}

template <size_t I = 0, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(const tuple<U...> &_t) {
    if (!I) {
        string _tmp_color = _color.back();
        ++_tmp_color[3], _color.eb(_tmp_color);
        cerr << _color.back();
    }
    cerr << (I ? ", " : "("), _print_err(get<I>(_t)), _print_err<I+1, U...>(_t);
}

template <size_t I = 0, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(tuple<U...> &) {
    cerr << ")" << (_color.pb(), _color.back());
}

template <size_t I = 0, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(tuple<U...> &_t) {
    if (!I) {
        string _tmp_color = _color.back();
        ++_tmp_color[3], _color.eb(_tmp_color);
        cerr << _color.back();
    }
    cerr << (I ? ", " : "("), _print_err(get<I>(_t)), _print_err<I+1, U...>(_t);
}

#endif
