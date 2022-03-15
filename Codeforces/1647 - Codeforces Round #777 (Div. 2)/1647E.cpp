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
#define SZ(x) ((int)(x).size())

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

void solve() {
    int N; cin >> N;
    
    int id_max = 0, id_bye = 0;
    vector<int> P(N), A(N), deg_i(N, 0);
    for (int i = 0; i < N; ++i) cin >> P[i], --P[i], ++deg_i[P[i]];
    for (int i = 0; i < N; ++i) cin >> A[i], chmax(id_max, A[i]);
    for (int i = 0; i < N; ++i) id_bye += !deg_i[i];
    
    int R = (id_max - N) / id_bye;
    vector<int> jump(N), base = P, tmp;
    iota(ALL(jump), 0);
    for (int exp = R; exp; exp >>= 1) {
        if (exp & 1) for (int &x : jump) x = base[x];
        tmp = base;
        for (int &x : base) x = tmp[x];
    }
    
    // debug(jump);
    
    vector<int> app(N+1, -1), start(N, -1), lbound(N, N);
    for (int i = 0; i < N; ++i) {
        if (A[i] <= N) app[A[i]] = i;
        if (start[jump[i]] == -1) start[jump[i]] = i;
        else lbound[i] = start[jump[i]];
    }
    
    // debug(app);
    // debug(start);
    // debug(lbound);
    
    set<int> left;
    vector<int> ans(N+1, -1);
    for (int i = 1; i <= N; ++i) left.ee(i);
    for (int i = 1; i <= N; ++i) {
        if (app[i] != -1) ans[start[app[i]]] = i, left.erase(i);
    }
    
    // debug(ans, left);
    
    for (int i = 0; i < N; ++i) {
        if (ans[i] == -1) ans[i] = *left.lower_bound(ans[lbound[i]]), left.erase(ans[i]);
    }
    
    for (int i = 0; i < N; ++i) cout << ans[i] << " \n"[i == N-1];
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
