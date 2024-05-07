#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int mod = 998'244'353;
const int RT = 3;

int fpow(int base, int exp = mod-2, int ans = 1) {
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        exp >>= 1, base = base * base % mod;
    }
    return ans;
}

struct NTT {
    vector<int> w;
    int maxn;
    NTT(int N = 1) { init(N); }
    void init(int N) {
        maxn = (1 << (__lg(N) + 1));
        w.assign(maxn, 0), w[0] = 1;
        int dw = fpow(RT, (mod - 1) / maxn);
        for (int i = 1; i < maxn; ++i) w[i] = w[i-1] * dw % mod;
    }
    void bitrev(vector<int> &a, int n) {
        int i = 0;
        for (int j = 1; j < n - 1; ++j) {
            for (int k = n >> 1; (i ^= k) < k; k >>= 1);
            if (j < i) swap(a[i], a[j]);
        }
    }
    void operator()(vector<int> &a, int n, bool inv = false) { /// 0 <= a[i] < mod
        bitrev(a, n);
        for (int L = 2; L <= n; L <<= 1) {
            int dx = maxn / L, dl = L >> 1;
            for (int i = 0; i < n; i += L) {
                for (int j = i, x = 0; j < i + dl; ++j, x += dx) {
                    int tmp = a[j + dl] * w[x] % mod;
                    if ((a[j + dl] = a[j] - tmp) < 0) a[j + dl] += mod;
                    if ((a[j] += tmp) >= mod) a[j] -= mod;
                }
            }
        }
        if (inv) {
            reverse(begin(a) + 1, begin(a) + n);
            int invn = fpow(n);
            for (int i = 0; i < n; ++i) a[i] = a[i] * invn % mod;
        }
    }
};

void solve() {
    int N, K; cin >> N >> K;
    
    if (K == 1) { print(1); return; }
    
    /// this is called "Stirling numbers of the second kind" ///
    
    // Vec<2, int> ways(N+1, K+1, 0); ways[0][0] = 1;
    // for (int i = 1; i <= N; ++i) {
    //     for (int j = 1; j <= K; ++j) {
    //         ways[i][j] = (ways[i-1][j-1] + ways[i-1][j] * j) % mod;
    //     }
    //     debug(i, ways[i]);
    // }
    
    vector<int> fac(N+1, 1), ifac(N+1, 1);
    for (int i = 1; i <= N; ++i) fac[i] = fac[i-1] * i % mod;
    ifac[N] = fpow(fac[N]);
    for (int i = N; i >= 1; --i) ifac[i-1] = ifac[i] * i % mod;
    
    auto calc = [&](int n, int k) -> int {
        /// use NTT to calculate all S(n, k) for some fixed n in O(n log n) ///
        
        // debug(n, k);
        
        int len = (1 << (__lg(n+1) + 2));
        
        static NTT ntt;
        ntt.init(len);
        
        vector<int> p(len, 0), q(len, 0), s(len, 0);
        for (int i = 0; i <= n; ++i) p[i] = (i & 1 ? mod - ifac[i] : ifac[i]);
        for (int i = 0; i <= n; ++i) q[i] = fpow(i, n) * ifac[i] % mod;
        // debug(p);
        // debug(q);
        ntt(p, len), ntt(q, len);
        for (int i = 0; i < len; ++i) s[i] = p[i] * q[i] % mod;
        // for (int i = 0; i < len; ++i) {
        //     for (int j = 0; j <= i; ++j) s[i] = (s[i] + p[j] * q[i-j]) % mod;
        // }
        ntt(s, len, true);
        // debug(s);
        
        return accumulate(begin(s), begin(s) + k + 1, int(0)) % mod;
        // return accumulate(begin(ways[n]), begin(ways[n]) + k + 1, int(0)) % mod;
    };
    
    vector<int> dp(N+1, 0);
    for (int i = N; i >= 1; --i) {
        // debug(i);
        dp[i] = calc((N-1)/i+1, min(K, (N-1)/i+1));
        // debug(i, dp[i]);
        for (int j = i+i; j <= N; j += i) dp[i] = (dp[i] - dp[j] + mod) % mod;
        if (N % i) dp[i] = (dp[i] - dp[N] + mod) % mod;
        // debug(i, dp[i]);
    }
    print(dp[1]);
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

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using i128 = __int128;
#define int i64
using f80 = long double;
using f128 = __float128;
#define double f80
using pii = pair<int, int>;
template <typename T> using Prior = std::priority_queue<T>;
template <typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

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

template <size_t D, typename T> struct Vec : vector<Vec<D-1, T>> {
    static_assert(D >= 1, "Vector dimension must be greater than zero!");
    template <typename... Args> Vec(int n = 0, Args... args) : vector<Vec<D-1, T>>(n, Vec<D-1, T>(args...)) {}
};

template <typename T> struct Vec<1, T> : vector<T> {
    Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
};

template <class F>
inline constexpr decltype(auto) lambda_fix(F&& f) {
    return [f = std::forward<F>(f)](auto&&... args) {
        return f(f, std::forward<decltype(args)>(args)...);
    };
}

#ifdef local
#define fastIO() void()
#define debug(...) \
    _color.emplace_back("\u001b[31m"), \
    fprintf(stderr, "%sAt [%s], line %d: (%s) = ", _color.back().c_str(), __FUNCTION__, __LINE__, #__VA_ARGS__), \
    _do(__VA_ARGS__), _color.pop_back(), \
    fprintf(stderr, "%s", _color.back().c_str())
#define print(...) \
    fprintf(stdout, "%s", "\u001b[36m"), \
    _P(__VA_ARGS__), \
    fprintf(stdout, "%s", "\u001b[0m")

deque<string> _color{"\u001b[0m"};

template <typename T> concept is_string = is_same_v<T, string&> or is_same_v<T, const string&>;
template <typename T> concept is_iterable = requires (T _t) {begin(_t);};

template <typename T> inline void _print_err(T &&_t);
template <typename T> inline void _print_err(T &&_t) requires is_iterable<T> and (not is_string<T>);
template <size_t I, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(const tuple<U...> &);
template <size_t I, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(const tuple<U...> &_t);
template <size_t I, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(tuple<U...> &);
template <size_t I, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(tuple<U...> &_t);
template <typename T, typename U> ostream& operator << (ostream &os, const pair<T, U> &_tu);

inline void _do() {cerr << "\n";};
template <typename T> inline void _do(T &&_t) {_print_err(_t), cerr << "\n";}
template <typename T, typename ...U> inline void _do(T &&_t, U &&..._u) {_print_err(_t), cerr << ", ", _do(_u...);}
#else
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#define debug(...) void()
#define print(...) _P(__VA_ARGS__)
#endif

inline void _P() {cout << "\n";};
template <typename T> inline void _P(T &&_t) {cout << _t << "\n";}
template <typename T, typename ...U> inline void _P(T &&_t, U &&..._u) {cout << _t << " ", _P(_u...);}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template <typename T, typename U> bool chmin(T &lhs, U rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

/// below are Fast I/O and _print_err templates ///

/*
/// Fast I/O by FHVirus ///
/// https://fhvirus.github.io/blog/2020/fhvirus-io/ ///

#include <unistd.h>

const int S = 65536;

int OP = 0;
char OB[S];

inline char RC() {
    static char buf[S], *p = buf, *q = buf;
    return p == q and (q = (p = buf) + read(0, buf, S)) == buf ? -1 : *p++;
}

inline int RI() {
    static char c;
    int a;
    while (((c = RC()) < '0' or c > '9') and c != '-' and c != -1);
    if (c == '-') {
        a = 0;
        while ((c = RC()) >= '0' and c <= '9') a *= 10, a -= c ^ '0';
    }
    else {
        a = c ^ '0';
        while ((c = RC()) >= '0' and c <= '9') a *= 10, a += c ^ '0';
    }
    return a;
}

inline void WI(int n, char c = '\n') {
    static char buf[20], p;
    if (n == 0) OB[OP++] = '0';
    p = 0;
    if (n < 0) {
        OB[OP++] = '-';
        while (n) buf[p++] = '0' - (n % 10), n /= 10;
    }
    else {
        while (n) buf[p++] = '0' + (n % 10), n /= 10;
    }
    for (--p; p >= 0; --p) OB[OP++] = buf[p];
    OB[OP++] = c;
    if (OP > S-20) write(1, OB, OP), OP = 0;
}

/// Fast I/O by FHVirus ///
/// https://fhvirus.github.io/blog/2020/fhvirus-io/ ///
*/

#ifdef local

template <typename T> inline void _print_err(T &&_t) {cerr << _t;}

template <typename T> inline void _print_err(T &&_t) requires is_iterable<T> and (not is_string<T>) {
    string _tmp_color = _color.back();
    ++_tmp_color[3], _color.emplace_back(_tmp_color);
    cerr << _color.back() << "[";
    for (bool _first = true; auto &_x : _t) {
        if (!_first) cerr << ", ";
        _print_err(_x), _first = false;
    }
    cerr << "]" << (_color.pop_back(), _color.back());
}

template <typename T, typename U> ostream& operator << (ostream &os, const pair<T, U> &_tu) {
    string _tmp_color = _color.back();
    ++_tmp_color[3], _color.emplace_back(_tmp_color);
    cerr << _color.back() << "(";
    _print_err(_tu.first), cerr << ", ", _print_err(_tu.second);
    cerr << ")" << (_color.pop_back(), _color.back());
    return os;
}

template <size_t I = 0, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(const tuple<U...> &) {
    cerr << ")" << (_color.pop_back(), _color.back());
}

template <size_t I = 0, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(const tuple<U...> &_t) {
    if (!I) {
        string _tmp_color = _color.back();
        ++_tmp_color[3], _color.emplace_back(_tmp_color);
        cerr << _color.back();
    }
    cerr << (I ? ", " : "("), _print_err(get<I>(_t)), _print_err<I+1, U...>(_t);
}

template <size_t I = 0, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(tuple<U...> &) {
    cerr << ")" << (_color.pop_back(), _color.back());
}

template <size_t I = 0, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(tuple<U...> &_t) {
    if (!I) {
        string _tmp_color = _color.back();
        ++_tmp_color[3], _color.emplace_back(_tmp_color);
        cerr << _color.back();
    }
    cerr << (I ? ", " : "("), _print_err(get<I>(_t)), _print_err<I+1, U...>(_t);
}

#endif

#endif
