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

const int maxn = 1 << 20;

int BIT[4][maxn];

void Add(int num, int idx, int val = 1) {
    while (idx < maxn) BIT[num][idx] += val, idx += idx & -idx;
}

int Sum(int num, int idx, int ans = 0) {
    while (idx) ans += BIT[num][idx], idx -= idx & -idx;
    return ans;
}

void solve() {
    int N, M; cin >> N >> M;
    
    vector<int> A(N+1);
    for (int i = 1; i <= N; ++i) cin >> A[i], Add(A[i], i);
    
    int ans = 0;
    for (int _ = 1, x, y, z; _ <= M; ++_) {
        
        cin >> x >> y >> z, Add(A[x], x, -1), Add(A[x] = y, x);
        
        int L[4] = {0, Sum(1, z), Sum(2, z), Sum(3, z)};
        int T[4] = {0, Sum(1, N), Sum(2, N), Sum(3, N)};
        int S = 1*T[1] + 2*T[2] + 3*T[3];
        if (S % 2) {
            // debug(_, -1, "S odd"s);
            ans += -1; continue;
        }
        S /= 2;
        
        int mn = 1 * min(z, T[1]) + 2 * min(z - min(z, T[1]), T[2]) + 3 * min(z - min(z, T[1] + T[2]), T[3]);
        int mx = 3 * min(z, T[3]) + 2 * min(z - min(z, T[3]), T[2]) + 1 * min(z - min(z, T[3] + T[2]), T[1]);
        if (mx < S or S < mn) {
            // debug(_, -1, T[1], T[2], T[3], mn, mx, S, "unreachable"s);
            ans += -1; continue;
        }
        
        int D = (1*L[1] + 2*L[2] + 3*L[3]) - S;
        if (T[2] == 0 and D % 2) {
            // debug(_, -1, "all odd"s);
            ans += -1; continue;
        }
        
        if (D < 0) {
            L[1] = T[1] - L[1], L[2] = T[2] - L[2], L[3] = T[3] - L[3];
            D = -D;
        }
        
        int change_3_to_1 = min({L[3], T[1] - L[1], D / 2});
        ans += D - change_3_to_1;
        
        // debug(_, D - change_3_to_1);
        
    }
    cout << ans << "\n";
    
    for (int i = 1; i <= N; ++i) Add(A[i], i, -1);
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
