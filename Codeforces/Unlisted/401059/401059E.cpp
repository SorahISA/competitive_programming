#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

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

template <size_t D, typename T> struct Vec : public vector<Vec<D-1, T>> {
    static_assert(D >= 1, "Vector dimension must be greater than zero!");
    template <typename... Args> Vec(int n = 0, Args... args) : vector<Vec<D-1, T>>(n, Vec<D-1, T>(args...)) {}
};

template <typename T> struct Vec<1, T> : public vector<T> {
    Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
};

#ifdef local
#define fastIO() void()
#define debug(...) \
    _color.eb("\u001b[31m"),\
    cerr << _color.back() << "At [" << __FUNCTION__ << "], line " << __LINE__ << ": ",\
    cerr << "(" << #__VA_ARGS__ << ") = ", _do(__VA_ARGS__),\
    _color.pb(),\
    cerr << _color.back()
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
const int INF = INT_MAX;

vector<int> BIT(maxn, 0);

void Add(int idx, int val) {
    if (idx <= 0) return;
    while (idx < maxn) BIT[idx] += val, idx += idx & -idx;
}

int Sum(int idx, int ans = 0) {
    while (idx) ans += BIT[idx], idx -= idx & -idx;
    return ans;
}

void solve() {
    int N, Q; cin >> N >> Q;
    
    vector<int> g(maxn, 0);
    for (int i = 1; i <= N-1; ++i) cin >> g[i];
    
    set<tuple<int, int, int>> itv;
    itv.ee(-1, -1, -1);
    itv.ee(0, N+1, 0);
    itv.ee(N+2, N+2, -1);
    
    int op, l, r, c;
    auto it = begin(itv);
    while (Q--) {
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> c;
            // debug("before"s, itv);
            
            auto it_L = prev(itv.lower_bound({l, -INF, 0})); /// last L < l
            auto [oL_L, oR_L, oC_L] = *it_L;
            auto it_R = prev(itv.lower_bound({r+1, INF, 0})); /// first R > r
            auto [oL_R, oR_R, oC_R] = *it_R;
            
            for (it = it_L; it != next(it_R); ++it) {
                auto [L_L, R_L, C_L] = *it;
                auto [L_R, R_R, C_R] = *next(it);
                if (C_L > 0 and C_R > 0) Add(R_L, -g[R_L]);
            }
            it = itv.erase(it_L, next(it_R));
            
            chmin(oR_L, l-1), chmax(oL_R, r+1);
            if (c == oC_L) l = oL_L, oR_L = -1;
            if (c == oC_R) r = oR_R, oR_R = -1;
            if (oL_R <= oR_R) { /// add right
                it = itv.ee(oL_R, oR_R, oC_R).first;
                if (oC_R > 0 and get<2>(*next(it)) > 0) Add(oR_R, g[oR_R]);
            }
            if (l <= r) { /// add mid (true)
                it = itv.ee(l, r, c).first;
                if (get<2>(*next(it)) > 0) Add(r, g[r]);
            }
            if (oL_L <= oR_L) { /// add left
                it = itv.ee(oL_L, oR_L, oC_L).first;
                if (oC_L > 0 and get<2>(*next(it)) > 0) Add(oR_L, g[oR_L]);
            }
            
            // debug(" after"s, itv);
        }
        if (op == 2) {
            cin >> l >> r;
            cout << Sum(r-1) - Sum(l-1) << "\n";
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

/// below are Fast I/O and _print_err templates ///

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
