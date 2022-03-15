#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
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

void solve() {
    int N, M, K; cin >> N >> M;
    
    vector<int> A(N);
    for (int &x : A) cin >> x;
    sort(ALL(A));
    auto B = A;
    B.resize(unique(ALL(B)) - begin(B)), K = SZ(B);
    for (int &x : A) x = lower_bound(ALL(B), x) - begin(B);
    // debug(A, B);
    
    vector<pii> nums(K);
    for (int i = 0; i < K; ++i) nums[i].X = B[i];
    for (int &x : A) ++nums[x].Y;
    // debug(nums);
    
    vector<pii> bad(M);
    for (auto &[x, y] : bad) {
        cin >> x >> y;
        x = lower_bound(ALL(B), x) - begin(B);
        y = lower_bound(ALL(B), y) - begin(B);
    }
    // debug(bad);
    
    vector<int> ban[K];
    for (auto &[x, y] : bad) ban[x].eb(y), ban[y].eb(x);
    for (int i = 0; i < K; ++i) sort(ALL(ban[i]));
    
    // int min_need = min(K, K - (1 + (int)sqrt((2*K-1)*(2*K-1)-8*M)) / 2 + 3);
    int min_need = min(K, 2 * max(1 + (int)sqrt(8*M+1) / 2, (int)sqrt(N)) + 5);
    // debug(min_need);
    
    vector<int> good(K, 0);
    
    /// find max x ///
    for (int i = K-1; i >= K-min_need; --i) good[i] = 1;
    
    /// find max cnt[x] ///
    int lo_c = 0, hi_c = N;
    while (lo_c < hi_c) {
        int mi = (lo_c + hi_c + 1) >> 1, tmp = 0;
        for (auto [x, cnt] : nums) tmp += cnt >= mi;
        if (tmp >= min_need) lo_c = mi;
        else                 hi_c = mi - 1;
    }
    for (int i = K-1, left = min_need; i >= 0 and left; --i) {
        if (nums[i].Y >= lo_c) good[i] = 1, --left;
    }
    // debug(lo_c);
    
    /// find max x * cnt[x] ///
    int64_t lo_xc = 0, hi_xc = (int64_t)1E18;
    while (lo_xc < hi_xc) {
        int64_t mi = (lo_xc + hi_xc + 1) >> 1, tmp = 0;
        for (auto [x, cnt] : nums) tmp += (int64_t)x * cnt >= mi;
        if (tmp >= min_need) lo_xc = mi;
        else                 hi_xc = mi - 1;
    }
    for (int i = K-1, left = min_need; i >= 0 and left; --i) {
        if ((int64_t)nums[i].X * nums[i].Y >= lo_xc) good[i] = 1, --left;
    }
    // debug(lo_xc);
    
    // vector<int> goods;
    // for (int i = 0; i < K; ++i) {
        // if (good[i]) goods.eb(i);
    // }
    // debug(good, goods);
    
    // int64_t ans = 0;
    // for (int x : goods) {
        // int tok = 0;
        // for (int y : goods) {
            // if (x == y) continue;
            // while (tok < SZ(ban[x]) and ban[x][tok] < y) ++tok;
            // if (tok == SZ(ban[x]) or ban[x][tok] != y) {
                // chmax(ans, (int64_t)(nums[x].X + nums[y].X) * (nums[x].Y + nums[y].Y));
            // }
        // }
    // }
    // cout << ans << "\n";
    
    int64_t ans = 0;
    for (int i = 0; i < K; ++i) {
        if (!good[i]) continue;
        for (int j = 0, tok = 0; j < K; ++j) {
            if (i == j) continue;
            if (tok < SZ(ban[i]) and ban[i][tok] == j) ++tok;
            else chmax(ans, (int64_t)(nums[i].X + nums[j].X) * (nums[i].Y + nums[j].Y));
        }
    }
    cout << ans << "\n";
    
    assert(ans > 0);
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
