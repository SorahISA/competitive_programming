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

template <typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int INF = 1E5;

void solve() {
    int N; cin >> N;
    
    vector<int> len_same(26, 0);
    vector<string> VS;
    for (int i = 0; i < N; ++i) {
        string S; cin >> S;
        int flag_same = 1;
        for (int j = 1; j < SZ(S); ++j) flag_same &= S[j] == S[0];
        if (flag_same) len_same[S[0]-'A'] += SZ(S);
        else VS.eb(S);
    }
    
    for (string &S : VS) {
        int &fr = len_same[S[0]-'A'], &bk = len_same[S.back()-'A'];
        if (fr) S = string(fr, S[0]) + S, fr = 0;
        if (bk) S = S + string(bk, S.back()), bk = 0;
        for (char &c : S) if (len_same[c-'A']) return cout << "IMPOSSIBLE" << "\n", void();
    }
    
    set<int> alive;
    for (int i = 0; i < SZ(VS); ++i) alive.ee(i);
    for (int _t = 0, sz = SZ(alive); _t < 20000; ++_t, sz = SZ(alive)) {
        vector<int> perm(ALL(alive));
        shuffle(ALL(perm), rng);
        perm.eb(-1); /// prevent warning for j = perm[++_i] ///
        for (int _i = 1, i = perm[0], j = perm[1]; _i < sz; i = j, j = perm[++_i]) {
            if (!SZ(VS[i]) or !SZ(VS[j])) continue;
            if (VS[i].back() == VS[j][0]) VS[i] += VS[j], VS[j] = "", alive.erase(j);
        }
    }
    
    string ANS;
    for (string &S : VS) ANS += S;
    for (int i = 0; i < 26; ++i) if (len_same[i]) ANS += string(len_same[i], i+'A');
    debug(ANS);
    
    vector<pii> app(26, {INF, -1});
    for (int i = 0; i < SZ(ANS); ++i) chmin(app[ANS[i]-'A'].X, i), chmax(app[ANS[i]-'A'].Y, i);
    for (int i = 0; i < 26; ++i) {
        for (int p = app[i].X; p <= app[i].Y; ++p) {
            if (ANS[p] != (char)(i+'A')) return cout << "IMPOSSIBLE" << "\n", void();
        }
    }
    cout << ANS << "\n";
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
