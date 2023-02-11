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

struct DSU {
    
    vector<int> p, sz;
    stack<array<int, 4>> stk;
    
    int R(int x) {return x ^ p[x] ? R(p[x]) : x;}
    
    int U(int x, int y) {
        x = R(x), y = R(y);
        if (sz[x] > sz[y]) swap(x, y);
        stk.ee(array{x, p[x], y, sz[y]});
        if (x != y) return sz[y] += sz[x], p[x] = y, 1;
        return 0;
    }
    
    void undo() {
        auto op = stk.top(); stk.pop();
        p[op[0]] = op[1], sz[op[2]] = op[3];
    }
    
    void init(int n) {
        p.resize(n), iota(ALL(p), 0);
        sz.assign(n, 1);
    }
    
} dsu;

deque<array<int, 3>> stk;

void enqueue(int x, int y) {
    // debug("enqueue"s, x, y);
    static int id = 0;
    dsu.U(x, y);
    stk.eb(array{id++, x, y});
}

void dequeue() {
    static int tok = -1;
    
    if (stk.back()[0] <= tok) {
        // debug("dequeue"s, "simple"s);
        dsu.undo(), stk.pb();
        return;
    }
    
    deque<array<int, 3>> op_old, op_new;
    do {
        auto op = stk.back(); dsu.undo(), stk.pb();
        if (op[0] <= tok) op_old.ef(op);
        else              op_new.ef(op);
        if (op[0] == tok) break;
    } while (SZ(stk) and SZ(op_old) < SZ(op_new));
    
    if (!SZ(op_old)) {
        // debug("dequeue"s, "reverse new"s);
        op_new.pf();
        tok = op_new.back()[0];
        while (SZ(op_new)) {
            auto op = op_new.back(); op_new.pb();
            dsu.U(op[1], op[2]), stk.eb(op);
        }
    }
    else {
        // debug("dequeue"s, "pop"s);
        op_old.pb();
        for (auto op : op_new) dsu.U(op[1], op[2]), stk.eb(op);
        for (auto op : op_old) dsu.U(op[1], op[2]), stk.eb(op);
    }
    
    decltype(op_old)().swap(op_old);
    decltype(op_new)().swap(op_new);
}

void solve() {
    int N, M, Q; cin >> N >> M >> Q;
    
    dsu.init(2*N);
    vector<pii> edges(M);
    for (auto &[u, v] : edges) cin >> u >> v, --u, --v;
    for (int i = 0; i < M; ++i) edges.eb(edges[i]);
    
    vector<int> ans(2*M, -1);
    for (int L = 0, R = 0; R < 2*M; ++R) {
        enqueue(2 * edges[R].first, 2 * edges[R].second + 1);
        enqueue(2 * edges[R].first + 1, 2 * edges[R].second);
        while (dsu.R(2 * edges[R].first) == dsu.R(2 * edges[R].first + 1)) {
            // debug("pop"s, L, R);
            dequeue(), dequeue(), ++L;
            // debug(stk);
        }
        ans[R] = L;
        // debug("\n"s, stk);
    }
    
    // debug(ans);
    
    for (int i = 0, L, R; i < Q; ++i) {
        cin >> L >> R, --L, --R;
        if (R >= ans[L+M-1] - 1) cout << "NO" << "\n";
        else                     cout << "YES" << "\n";
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
