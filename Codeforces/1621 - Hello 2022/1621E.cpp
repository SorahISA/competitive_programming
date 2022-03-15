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

inline int divceil(int x, int y) {return (x - 1) / y + 1;}

void solve() {
    int N, M; cin >> N >> M;
    
    vector<int> teach(N);
    for (int &x : teach) cin >> x;
    sort(RALL(teach)), teach.resize(M), reverse(ALL(teach));
    // debug(teach);
    
    int tok = 0;
    vector<pii> stud[M];
    vector<int> sum_stud(M, 0);
    for (int i = 0; i < M; ++i) {
        int sz; cin >> sz, stud[i].resize(sz);
        for (pii &x : stud[i]) cin >> x.X, x.Y = tok++, sum_stud[i] += x.X;
        // debug(stud[i]);
    }
    // debug(sum_stud);
    
    vector<int> id(M), inv_id(M);
    iota(ALL(id), 0);
    sort(ALL(id), [&](int x, int y) {
        return divceil(sum_stud[x], SZ(stud[x])) < divceil(sum_stud[y], SZ(stud[y]));
    });
    for (int i = 0; i < M; ++i) inv_id[id[i]] = i;
    // debug(id, inv_id);
    
    vector<int> avg(M);
    for (int i = 0; i < M; ++i) avg[i] = divceil(sum_stud[id[i]], SZ(stud[id[i]]));
    // debug(avg);
    
    vector<int> lst(M, 0), now(M, 0), nxt(M, 0);
    for (int i = 0; i < M; ++i) {
        if (i > 0)   lst[i] = avg[i] <= teach[i-1];
        if (true)    now[i] = avg[i] <= teach[i];
        if (i < M-1) nxt[i] = avg[i] <= teach[i+1];
    }
    partial_sum(ALL(lst), begin(lst));
    partial_sum(ALL(now), begin(now));
    partial_sum(ALL(nxt), begin(nxt));
    // debug(lst), debug(now), debug(nxt);
    
    string ans(tok, '0');
    for (int _i = 0, i = id[0]; _i < M; i = id[++_i]) {
        for (pii x : stud[i]) {
            int new_avg = divceil(sum_stud[i] - x.X, SZ(stud[i]) - 1);
            int p = upper_bound(ALL(avg), new_avg) - begin(avg), cnt = 0;
            if (p < _i) {
                cnt = (p ? now[p-1] : 0)
                    + (nxt[_i-1] - (p ? nxt[p-1] : 0))
                    + (now[M-1] - now[_i])
                    + (new_avg <= teach[p]);
            }
            else if (p > _i+1) {
                cnt = (_i ? now[_i-1] : 0)
                    + (lst[p-1] - lst[_i])
                    + (now[M-1] - now[p-1])
                    + (new_avg <= teach[p-1]);
            }
            else {
                cnt = (_i ? now[_i-1] : 0)
                    + (now[M-1] - now[_i])
                    + (new_avg <= teach[_i]);
            }
            ans[x.Y] = cnt == M ? '1' : '0';
            // debug(i, _i, p, x.Y, cnt, avg[_i], new_avg);
        }
        if (_i == M-1) break;
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}
