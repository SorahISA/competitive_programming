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

const int maxc = 1E9 + 5;
const int mod = 1E9 + 7;

void solve() {
    int N; cin >> N;
    
    vector<int> tree_x, tree_y;
    for (int i = 0, x, y; i < N; ++i) cin >> x >> y, tree_x.eb(x), tree_y.eb(y);
    sort(ALL(tree_x)), sort(ALL(tree_y));
    
    int Q; cin >> Q;
    
    vector<int> well_x, well_y;
    for (int i = 0, x, y; i < Q; ++i) cin >> x >> y, well_x.eb(x), well_y.eb(y);
    sort(ALL(well_x)), sort(ALL(well_y));
    
    int ans = 0;
    
    /// sum of p^2 = s2
    /// sum of p^1 = s1
    /// sum of p^0 = s0
    /// append place at last+k
    /// sum of (p+k)^2 = s2 + 2*s1*k + s0*k*k
    /// sum of (p+k)^1 = s1 + s0*k
    /// sum of (p+k)^0 = s0 + 1
    
    auto calc = [&](vector<int> &tree, vector<int> &well) -> void {
        // debug(tree, well);
        int s0 = 1, s1 = 0, s2 = 0, dx;
        for (int i = 0; i < Q; ++i) {
            while (s0 < N and tree[s0] <= well[i]) {
                dx = tree[s0] - tree[s0-1];
                s2 = (s2 + 2 * s1 * dx + s0 * dx % mod * dx) % mod;
                s1 = (s1 + s0 * dx) % mod;
                s0 = (s0 + 1);
            }
            // debug(s0, s1, s2);
            dx = well[i] - tree[s0-1];
            if (dx >= 0) ans = (ans + s2 + 2 * s1 * dx + s0 * dx % mod * dx) % mod;
        }
    };
    
    calc(tree_x, well_x);
    reverse(ALL(tree_x)); for (int &x : tree_x) x = -x;
    reverse(ALL(well_x)); for (int &x : well_x) x = -x;
    calc(tree_x, well_x);
    
    calc(tree_y, well_y);
    reverse(ALL(tree_y)); for (int &y : tree_y) y = -y;
    reverse(ALL(well_y)); for (int &y : well_y) y = -y;
    calc(tree_y, well_y);
    
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}
