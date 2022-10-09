#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int int64_t
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

template<typename T> struct Vec<1, T> : public vector<T> {
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

void SCO(bool atk_A, string A, int sc_A, int sc_D, string D) {
    if (atk_A) cout << "ATK " << A << " | " << to_string(sc_A) << " : " << to_string(sc_D) << " | " << D << " DEF" << "\n";
    else       cout << "DEF " << A << " | " << to_string(sc_A) << " : " << to_string(sc_D) << " | " << D << " ATK" << "\n";
}

void RES(int tp, bool curse) {
    if (tp == 0) cout << "Match in Progress" << "\n";
    if (tp == 'A') cout << "Attackers Win" << (curse ? ", 9-3 Curse!" : "") << "\n";
    if (tp == 'D') cout << "Defenders Win" << (curse ? ", 9-3 Curse!" : "") << "\n";
}

void WA() {
    cout << "something went wrong :(" << "\n";
}

void solve() {
    int N; cin >> N;
    string A, D; cin >> A >> D;
    
    string game; cin >> game;
    
    int sc_A = 0, sc_D = 0;
    for (int i = 0; i < min(N, 12); ++i) {
        sc_A += (game[i] == 'A');
        sc_D += (game[i] == 'D');
    }
    
    int curse = (sc_A == 9 ? 'A' : (sc_D == 9 ? 'D' : 0));
    bool valid = true;
    
    for (int i = 12; i < min(N, 24); ++i) {
        if (max(sc_A, sc_D) >= 13) valid = false;
        sc_A += (game[i] == 'D');
        sc_D += (game[i] == 'A');
    }
    if (sc_A != sc_D and N > 24) valid = false;
    
    for (int i = 24; i < N; ++i) {
        if (abs(sc_A - sc_D) >= 2) valid = false;
        sc_A += ((i & 1) ^ (game[i] == 'A'));
        sc_D += ((i & 1) ^ (game[i] == 'D'));
    }
    
    if (!valid) WA();
    else {
        bool atk_A = (N <= 12 or (N > 24 and (N & 1)));
        
        SCO(atk_A, A, sc_A, sc_D, D);
        
        if (max(sc_A, sc_D) <= 12 or abs(sc_A - sc_D) < 2) RES(0, false);
        else if (atk_A ^ (sc_A < sc_D)) RES('A', curse == (atk_A ? 'D' : 'A'));
        else                            RES('D', curse == (atk_A ? 'A' : 'D'));
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Match " << _ << ":\n";
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
