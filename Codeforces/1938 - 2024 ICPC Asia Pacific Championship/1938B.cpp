#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int penalty = 1'000'000;

void solve() {
    int N, M; cin >> N >> M;
    
    vector<pii> coord(N);
    for (auto &[x, y] : coord) cin >> x >> y;
    
    vector<map<int, int>> adj(N);
    vector<int> deg(N, 0);
    for (int i = 0; i < M; ++i) {
        int u, v, a; cin >> u >> v >> a, --u, --v;
        adj[u][v] = adj[v][u] = a;
        ++deg[u], ++deg[v];
    }
    
    map<tuple<int, int, int>, int> score4;
    map<tuple<int, int>, int> score3;
    vector<int> vis(N, 0);
    prior<pii> pq;
    for (int i = 0; i < N; ++i) pq.ee(deg[i], i);
    
    int ans = 0;
    while (SZ(pq)) {
        auto [d, o] = pq.top(); pq.pop();
        if (vis[o]) continue;
        vis[o] = 1;
        
        for (auto [u, ou] : adj[o]) for (auto [v, ov] : adj[o]) for (auto [w, ow] : adj[o]) {
            if (u < v and v < w and adj[u].contains(v) and adj[u].contains(w) and adj[v].contains(w)) {
                /// K4: {o, u, v, w} ///
                int base = ou + ov + ow + adj[u][v] + adj[u][w] + adj[v][w];
                chmax(ans, base);
                
                /// K5 - e: {o, u, v, w, ???} ///
                array<int, 4> arr{o, u, v, w};
                sort(ALL(arr));
                if (score4.contains({arr[0], arr[1], arr[2]})) chmax(ans, base + score4[{arr[0], arr[1], arr[2]}] - penalty);
                if (score4.contains({arr[0], arr[1], arr[3]})) chmax(ans, base + score4[{arr[0], arr[1], arr[3]}] - penalty);
                if (score4.contains({arr[0], arr[2], arr[3]})) chmax(ans, base + score4[{arr[0], arr[2], arr[3]}] - penalty);
                if (score4.contains({arr[1], arr[2], arr[3]})) chmax(ans, base + score4[{arr[1], arr[2], arr[3]}] - penalty);
                
                int ab = adj[arr[0]][arr[1]], ac = adj[arr[0]][arr[2]], ad = adj[arr[0]][arr[3]];
                int bc = adj[arr[1]][arr[2]], bd = adj[arr[1]][arr[3]], cd = adj[arr[2]][arr[3]];
                chmax(score4[{arr[0], arr[1], arr[2]}], ad + bd + cd);
                chmax(score4[{arr[0], arr[1], arr[3]}], ac + bc + cd);
                chmax(score4[{arr[0], arr[2], arr[3]}], ab + bc + bd);
                chmax(score4[{arr[1], arr[2], arr[3]}], ab + ac + ad);
            }
            else if (u < v and v == w and adj[u].contains(v)) {
                /// K3: {o, u, v} ///
                int base = ou + ov + adj[u][v];
                chmax(ans, base);
                
                /// K4 - e: {o, u, v, ???} ///
                array<int, 3> arr{o, u, v};
                sort(ALL(arr));
                if (score3.contains({arr[0], arr[1]})) chmax(ans, base + score3[{arr[0], arr[1]}] - penalty);
                if (score3.contains({arr[0], arr[2]})) chmax(ans, base + score3[{arr[0], arr[2]}] - penalty);
                if (score3.contains({arr[1], arr[2]})) chmax(ans, base + score3[{arr[1], arr[2]}] - penalty);
                
                int ab = adj[arr[0]][arr[1]], ac = adj[arr[0]][arr[2]], bc = adj[arr[1]][arr[2]];
                chmax(score3[{arr[0], arr[1]}], ac + bc);
                chmax(score3[{arr[0], arr[2]}], ab + bc);
                chmax(score3[{arr[1], arr[2]}], ab + ac);
            }
            else if (u == v and v == w) {
                /// K2: {o, u} ///
                chmax(ans, ou);
            }
        }
        
        for (auto [x, a] : adj[o]) adj[x].erase(o), pq.ee(--deg[x], x);
        adj[o].clear(), deg[o] = 0;
    }
    print(ans);
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
#define print(...) \
    fprintf(stdout, "%s", "\u001b[36m"), \
    _P(__VA_ARGS__), \
    fprintf(stdout, "%s", "\u001b[0m")

deque<string> _color{"\u001b[0m"};

template <typename T> concept is_string = is_same_v<T, string&> or is_same_v<T, const string&>;
template <typename T> concept is_iterable = requires (T _t) {begin(_t);};

template <typename T> inline void _print_err(T &&_t);
template <typename T> inline void _print_err(T &&_t) requires is_iterable<T> and (not is_string<T>);
template <size_t I, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(const tuple<U...> &);
template <size_t I, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(const tuple<U...> &_t);
template <size_t I, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(tuple<U...> &);
template <size_t I, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(tuple<U...> &_t);
template <typename T, typename U> ostream& operator << (ostream &os, const pair<T, U> &_tu);

inline void _do() {cerr << "\n";};
template <typename T> inline void _do(T &&_t) {_print_err(_t), cerr << "\n";}
template <typename T, typename ...U> inline void _do(T &&_t, U &&..._u) {_print_err(_t), cerr << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#define print(...) _P(__VA_ARGS__)
#endif

inline void _P() {cout << "\n";};
template <typename T> inline void _P(T &&_t) {cout << _t << "\n";}
template <typename T, typename ...U> inline void _P(T &&_t, U &&..._u) {cout << _t << " ", _P(_u...);}

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
