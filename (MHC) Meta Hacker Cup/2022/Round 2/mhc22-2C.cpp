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

const int mod = 1E9 + 7;
const int maxc = 1E7;

vector<int> fact(maxc), ifact(maxc);

int fpow(int base, int exp = mod-2, int ans = 1) {
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        base = base * base % mod, exp >>= 1;
    }
    return ans;
}

int cnm(int n, int m) {
    if (n < m) return 0;
    return fact[n] * ifact[m] % mod * ifact[n-m] % mod;
}

void solve() {
    int N, K; cin >> N >> K;
    
    int w_1 = 0, c_1 = 0, c_lo = 0, c_mi = 0, c_hi = 0;
    cin >> c_1 >> w_1, c_mi += c_1;
    for (int i = 2, c, w; i <= N; ++i) {
        cin >> c >> w;
        if (w <  w_1) c_lo += c;
        if (w == w_1) c_mi += c;
        if (w >  w_1) c_hi += c;
    }
    
    // debug(K, c_lo, c_mi, c_hi, c_1);
    
    int pick_w1 = (cnm(c_lo + c_mi, K + 1) - cnm(c_lo, K + 1) + mod) * fpow(cnm(c_lo + c_mi + c_hi, K + 1)) % mod;
    int pick_c1 = c_1 * fpow(c_mi) % mod * pick_w1 % mod;
    
    cout << pick_c1 << "\n";
}

void init() {
    fact[0] = 1;
    for (int i = 1; i < maxc; ++i) fact[i] = fact[i-1] * i % mod;
    ifact[maxc-1] = fpow(fact[maxc-1]);
    for (int i = maxc-1; i >= 1; --i) ifact[i-1] = ifact[i] * i % mod;
}

int32_t main() {
    fastIO();
    init();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}
