#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

struct SegTree {
    
    struct Node {
        int mode, mode_cnt;
    };
    
    vector<Node> seg;
    int maxn;
    
    SegTree(int N) {init(N);}
    void init(int N) {
        maxn = (1 << (__lg(N) + 1));
        seg.assign(maxn<<1, Node{.mode = 0, .mode_cnt = 0});
    }
    
    void merge(Node &now, Node lt, Node rt) {
        if (lt.mode == rt.mode) {
            now.mode = lt.mode;
            now.mode_cnt = lt.mode_cnt + rt.mode_cnt;
        }
        else if (lt.mode_cnt >= rt.mode_cnt) {
            now.mode = lt.mode;
            now.mode_cnt = lt.mode_cnt - rt.mode_cnt;
        }
        else {
            now.mode = rt.mode;
            now.mode_cnt = rt.mode_cnt - lt.mode_cnt;
        }
    }
    
    void modify_point_value(int qX, int val) {
        seg[qX += maxn] = Node{.mode = val, .mode_cnt = 1};
        while ((qX >>= 1) >= 1) merge(seg[qX], seg[qX<<1], seg[qX<<1|1]);
    }
    
    Node query_range_absmode(int qL, int qR) {return query_range_absmode(qL, qR, 1, 0, maxn-1);}
    Node query_range_absmode(int qL, int qR, int now, int nL, int nR) {
        if (qL <= nL and nR <= qR) return seg[now];
        
        int nM = (nL + nR) >> 1;
        Node ans{.mode = 0, .mode_cnt = 0};
        if (qL <= nM) merge(ans, ans, query_range_absmode(qL, qR, now<<1,   nL,   nM));
        if (nM <  qR) merge(ans, ans, query_range_absmode(qL, qR, now<<1|1, nM+1, nR));
        
        return ans;
    }
    
};

void solve() {
    int N, Q; cin >> N >> Q;
    
    vector<int> A(N);
    for (int &x : A) cin >> x;
    
    SegTree seg(N);
    rank_tree<pii> rks;
    set<int> non_zero;
    for (int i = 0; i < N; ++i) {
        seg.modify_point_value(i, A[i]);
        rks.insert({A[i], i});
        if (A[i] != 0) non_zero.ee(i);
    }
    
    for (int q = 1; q <= Q; ++q) {
        int op; cin >> op;
        if (op == 1) {
            int x, y; cin >> x >> y, --x;
            rks.erase({A[x], x});
            seg.modify_point_value(x, A[x] = y);
            rks.insert({A[x], x});
            if (A[x] != 0) non_zero.ee(x);
            else           non_zero.erase(x);
        }
        else if (op == 2) {
            int L, R, k; cin >> L >> R >> k, --L, --R;
            if (k == 1) continue;
            auto it = non_zero.lower_bound(L);
            while (it != end(non_zero) and *it <= R) {
                rks.erase({A[*it], *it});
                seg.modify_point_value(*it, A[*it] /= k);
                rks.insert({A[*it], *it});
                if (A[*it] != 0) it = next(it);
                else             it = non_zero.erase(it);
            }
        }
        else if (op == 3) {
            int L, R; cin >> L >> R, --L, --R;
            SegTree::Node ans = seg.query_range_absmode(L, R);
            if (int(rks.order_of_key({ans.mode, R+1}) - rks.order_of_key({ans.mode, L})) > (R - L + 1) / 2) {
                cout << ans.mode << "\n";
            }
            else {
                cout << -1 << "\n";
            }
        }
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
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

// #define int int64_t
#define double __float80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;
template <typename T> using rank_tree = __gnu_pbds::tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

template <class F>
inline constexpr decltype(auto) lambda_fix(F&& f) {
    return [f = std::forward<F>(f)](auto&&... args) {
        return f(f, std::forward<decltype(args)>(args)...);
    };
}

#ifdef local
#define fastIO() void()
#define debug(...) \
    _color.emplace_back("\u001b[31m"), \
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
