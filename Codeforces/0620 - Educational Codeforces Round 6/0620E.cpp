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

const int maxn = 1 << 19;
const int maxL = maxn << 1; /// max leaf

struct SegNode {
    int val, tag;
    SegNode(int _val = 0) : val(_val), tag(0) {}
};

vector<int> adj[maxn], time_i(maxn), time_o(maxn);
vector<SegNode> seg(maxL << 1);

void dfs(int now, int lst, int &tok) {
    time_i[now] = ++tok;
    for (int x : adj[now]) {
        if (x != lst) dfs(x, now, tok);
    }
    time_o[now] = ++tok;
}

void push_seg(SegNode &now, SegNode &lt, SegNode &rt) {
    lt.val = lt.tag = rt.val = rt.tag = now.tag;
    now.tag = 0;
}

void pull_seg(SegNode &now, SegNode &lt, SegNode &rt) {
    now.val = lt.val | rt.val;
}

void range_modify_chval(int qL, int qR, int val, int now = 1, int nL = 0, int nR = maxL-1) {
    if (qL <= nL and nR <= qR) return seg[now].val = seg[now].tag = val, void();
    
    if (seg[now].tag) push_seg(seg[now], seg[now<<1], seg[now<<1|1]);
    
    int nM = (nL + nR) >> 1;
    if (qL <= nM) range_modify_chval(qL, qR, val, now<<1,   nL,   nM);
    if (nM <  qR) range_modify_chval(qL, qR, val, now<<1|1, nM+1, nR);
    
    pull_seg(seg[now], seg[now<<1], seg[now<<1|1]);
}

SegNode range_query_bitor(int qL, int qR, int now = 1, int nL = 0, int nR = maxL-1) {
    if (qL <= nL and nR <= qR) return seg[now];
    
    if (seg[now].tag) push_seg(seg[now], seg[now<<1], seg[now<<1|1]);
    
    int nM = (nL + nR) >> 1;
    SegNode ans(seg[now].val), lt(0), rt(0);
    if (qL <= nM) lt = range_query_bitor(qL, qR, now<<1,   nL,   nM);
    if (nM <  qR) rt = range_query_bitor(qL, qR, now<<1|1, nM+1, nR);
    
    pull_seg(ans, lt, rt);
    return ans;
}

void solve() {
    int N, M; cin >> N >> M;
    
    vector<int> col(N);
    for (int &x : col) cin >> x, x = (int)1 << x;
    
    for (int i = 0, u, v; i < N-1; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].eb(v), adj[v].eb(u);
    }
    
    int tok = 0;
    dfs(0, -1, tok);
    
    for (int i = 0; i < N; ++i) {
        range_modify_chval(time_i[i], time_i[i], col[i]);
        range_modify_chval(time_o[i], time_o[i], col[i]);
    }
    
    int op, v, c;
    while (M--) {
        cin >> op;
        
        if (op == 1) {
            cin >> v >> c, --v, c = (int)1 << c;
            range_modify_chval(time_i[v], time_o[v], c);
        }
        
        if (op == 2) {
            cin >> v, --v;
            int ans = range_query_bitor(time_i[v], time_o[v]).val;
            cout << __builtin_popcountll(ans) << "\n";
            // debug(__builtin_popcountll(ans));
        }
        
        // for (int _tok = 0; SegNode &seg_n : seg) debug(_tok, bitset<60>(seg_n.val), seg_n.tag), ++_tok;
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
