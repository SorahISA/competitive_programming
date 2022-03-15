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

template <typename T> bool chmin(T &lhs, T rhs) {return lhs >= rhs ? lhs = rhs, 1 : 0;}
template <typename T> bool chmax(T &lhs, T rhs) {return lhs <= rhs ? lhs = rhs, 1 : 0;}

int N = 4;
vector<int> arr;

int query(int i, int j, int k) {
    cout << "? " << i << " " << j << " " << k << "\n" << flush;
    int ret; // = max({arr[i-1], arr[j-1], arr[k-1]}) - min({arr[i-1], arr[j-1], arr[k-1]});
    cin >> ret;
    if (ret == -1) exit(0);
    return ret;
}

void answer(int i, int j) {
    cout << "! " << i << " " << j << "\n" << flush;
    // if (arr[i-1] and arr[j-1]) debug("WRONG"s, arr, i, j), exit(0);
    // else debug("AC"s, arr, i, j);
}

void gen() {
    arr.resize(N);
    for (int i = 0; i < N; ++i) arr[i] = getRand(1, 3);
    arr[getRand(0, N-1)] = 0;
}

void solve() {
    cin >> N;
    
    // gen();
    
    int max_ans = 0, max_ans_id = 0;
    for (int i = 3; i <= N; ++i) {
        if (chmax(max_ans, query(1, 2, i))) max_ans_id = i;
    }
    
    int max_ans2 = 0, max_ans2_id = 0;
    for (int i = 2; i <= N; ++i) {
        if (i == max_ans_id) continue;
        if (chmax(max_ans2, query(1, max_ans_id, i))) max_ans2_id = i;
    }
    
    if (max_ans2_id == 2) {
        int chk_1 = query(1, 2, 3 + (max_ans_id == 3));
        int chk_2 = query(1, 2, max_ans_id);
        if (chk_1 < chk_2) answer(2, max_ans_id);
        else               answer(1, 2);
    }
    else {
        int chk_1 = query(1, max_ans_id, max_ans2_id);
        int chk_2 = query(2, max_ans_id, max_ans2_id);
        if (chk_1 >  chk_2) answer(1, max_ans_id);
        if (chk_1 <  chk_2) answer(2, max_ans_id);
        if (chk_1 == chk_2) answer(max_ans_id, max_ans2_id);
    }
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
