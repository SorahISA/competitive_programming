#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T>
using Prior = std::priority_queue<T>;
template <typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ef push_front
#define ee emplace
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) (int)(x).size()

#ifdef local
#define debug(...) \
    _color.eb("\u001b[31m"),\
    cerr << _color.back() << "In function '" << __FUNCTION__ << "', line " << __LINE__ << ": (" << #__VA_ARGS__ << ") = ",\
    _do(__VA_ARGS__),\
    _color.pb(),\
    cerr << _color.back()
#define fastIO()
deque<string> _color{"\u001b[0m"};

template <typename T> concept is_string = is_same_v<T, string&> or is_same_v<T, const string&>;
template <typename T> concept is_iterable = requires (T _t) {begin(_t);};

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

template <typename T, typename U> ostream& operator << (ostream &os, pair<T, U> &_tu) {
    string _tmp_color = _color.back();
    ++_tmp_color[3], _color.eb(_tmp_color);
    cerr << _color.back() << "(";
    _print_err(_tu.first), cerr << ", ", _print_err(_tu.second);
    cerr << ")" << (_color.pb(), _color.back());
    return os;
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

template <typename T> inline void _do(T &&_t) {_print_err(_t), cerr << "\n";}
template <typename T, typename ...U> inline void _do(T &&_t, U &&..._u) {_print_err(_t), cerr << ", ", _do(_u...);}
#else
#define debug(...) void()
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#endif

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template <typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

vector<int> p, sz, p_cc;

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
int U(int x, int y) {x = R(x), y = R(y); return x ^ y ? sz[y] += sz[x], p[x] = y, 1 : 0;}

int R_cc(int x) {return x ^ p_cc[x] ? p_cc[x] = R_cc(p_cc[x]) : x;}
int U_cc(int x, int y) {x = R_cc(x), y = R_cc(y); return x ^ y ? p_cc[x] = y, 1 : 0;}

void solve() {
    int N, M; cin >> N >> M;
    p.resize(N), iota(ALL(p), 0);
    sz.assign(N, 1);
    
    set<pii> st;
    for (int i = 0, a, b; i < M; ++i) {
        cin >> a >> b, --a, --b;
        st.insert({min(a, b), max(a, b)});
    }
    
    int cc_cnt = N;
    while (cc_cnt > 2'000) {
        int a = getRand(0, N-1), b = getRand(0, N-1);
        if (!st.count({min(a, b), max(a, b)})) cc_cnt -= U(a, b);
    }
    vector<vector<int>> adj_mat(cc_cnt, vector<int>(cc_cnt, 0));
    p_cc.resize(cc_cnt), iota(ALL(p_cc), 0);
    
    vector<int> cc(N, 0), bosses;
    for (int i = 0, cc_tok = 0; i < N; ++i) {
        if (R(i) == i) cc[i] = cc_tok++, bosses.eb(i);
    }
    
    for (auto [a, b] : st) {
        ++adj_mat[cc[R(a)]][cc[R(b)]];
        ++adj_mat[cc[R(b)]][cc[R(a)]];
    }
    
    int ans = cc_cnt;
    for (int x : bosses) {
        for (int y : bosses) {
            if (x != y and adj_mat[cc[x]][cc[y]] < sz[x] * sz[y]) ans -= U_cc(cc[x], cc[y]);
        }
    }
    cout << ans - 1 << "\n";
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
