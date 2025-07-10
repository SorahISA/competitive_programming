#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

constexpr int mod = 998'244'353;

template <typename T> struct M {
//   static T MOD; // change to constexpr if already known
  static constexpr T MOD = mod; // change to constexpr if already known
  T v;
  M(T x = 0) {
    v = (-MOD <= x and x < MOD) ? x : x % MOD;
    if (v < 0) v += MOD;
  }
  explicit operator T() const { return v; }
  bool operator==(const M &b) const { return v == b.v; }
  bool operator!=(const M &b) const { return v != b.v; }
  M operator-() { return M(-v); }
  M operator+(M b) { return M(v + b.v); }
  M operator-(M b) { return M(v - b.v); }
  M operator*(M b) { return M((__int128)v * b.v % MOD); }
  // change implementation to extgcd if MOD is not prime
  M operator/(M b) { return *this * b.inv(); }
  M pow(int b) const {
    M r(1);
    for (M a = *this; b; b >>= 1, a *= a)
      if (b & 1) r *= a;
    return r;
  }
  M inv() const { return pow(MOD - 2); }
  M operator+=(const M &b) {
    if ((v += b.v) >= MOD) v -= MOD;
    return *this;
  }
  M operator-=(const M &b) {
    if ((v -= b.v) < 0) v += MOD;
    return *this;
  }
  friend M &operator*=(M &a, M b) { return a = a * b; }
  friend M &operator/=(M &a, M b) { return a = a / b; }
  friend ostream& operator << (ostream &os, const M &a) { return os << a.v; }
};
using Mod = M<int>;
// template <> int Mod::MOD = 1'000'000'007;
constexpr int MOD = Mod::MOD;

template <typename T> /// n = |a| = |rt| = 2^k
void fft_(int n, vector<T> &a, vector<T> &rt, bool inv) {
  vector<int> br(n);
  for (int i = 1; i < n; i++) {
    br[i] = (i&1) ? br[i - 1] + n / 2 : br[i / 2] / 2;
    if (br[i] > i) swap(a[i], a[br[i]]);
  }
  for (int len = 2; len <= n; len *= 2)
    for (int i = 0; i < n; i += len)
      for (int j = 0; j < len / 2; j++) {
        int pos = n / len * (inv ? len - j : j);
        T u = a[i + j], v = a[i + j + len/2] * rt[pos];
        a[i + j] = u + v, a[i + j + len/2] = u - v;
      }
  if (T minv = T(1) / T(n); inv)
    for (T &x : a) x *= minv;
}
void fft(vector<complex<double>> &a, bool inv) {
  int n = a.size();
  vector<complex<double>> rt(n + 1);
  double arg = acos(-1) * 2 / n;
  for (int i = 0; i <= n; i++)
    rt[i] = {cos(arg * i), sin(arg * i)};
  fft_(n, a, rt, inv);
}
// (2^16)+1, 65537, 3
// 7*17*(2^23)+1, 998244353, 3
// 1255*(2^20)+1, 1315962881, 3
// 51*(2^25)+1, 1711276033, 29
void ntt(vector<Mod> &a, bool inv, Mod primitive_root = 3){
  int n = a.size();
  Mod root = primitive_root.pow((MOD - 1) / n);
  vector<Mod> rt(n + 1, 1);
  for (int i = 0; i < n; i++) rt[i + 1] = rt[i] * root;
  fft_(n, a, rt, inv);
}

vector<Mod> polymul(vector<Mod> a, vector<Mod> b) {
    int n = SZ(a), m = SZ(b);
    int sz = 2 << __lg(n+m-1);
    // debug(a);
    // debug(b);
    a.resize(sz), ntt(a, false);
    b.resize(sz), ntt(b, false);
    vector<Mod> c(sz);
    for (int i = 0; i < sz; ++i) c[i] = a[i] * b[i];
    ntt(c, true), c.resize(n+m-1);
    // vector<Mod> c(n+m-1);
    // for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) c[i+j] += a[i] * b[j];
    // debug(c);
    return c;
}

int fpow(int base, int exp = mod-2, int ans = 1) {
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        exp >>= 1, base = base * base % mod;
    }
    return ans;
}

void solve() {
    int N, M; cin >> N >> M;
    
    vector<int> A(N*M); cin >> A;
    sort(ALL(A));
    
    vector<Mod> fact(N*M+1, 1), ifac(N*M+1, 1);
    for (int i = 1; i <= N*M; ++i) fact[i] = fact[i-1] * i;
    ifac.back() = fact.back().inv();
    for (int i = N*M; i >= 1; --i) ifac[i-1] = ifac[i] * i;
    
    auto binom = [&](int n, int m) -> Mod { return (n < m or m < 0 ? 0 : fact[n] * ifac[m] * ifac[n-m]); };
    
    vector<Mod> X(N*M+1), Y(N*M+1), Z(N*M+1);
    for (int i = 0; i <= N*M; ++i) {
        X[i] = (i ? fact[i-1] * A[i-1] : 0);
        Y[i] = fact[N*M - i] * i;
        Z[i] = ifac[i];
    }
    
    reverse(ALL(X));
    auto XZ = polymul(X, Z);
    reverse(ALL(X));
    
    vector<Mod> F(N*M+1);
    for (int i = 0; i <= N*M; ++i) F[i] = XZ[N*M - i] * Y[i];
    // debug(F);
    
    // vector<Mod> f(N*M+1);
    // for (int k = 1; k <= N*M; ++k) for (int p = k; p <= N*M; ++p) {
    //     // f[k] += (fact[p-1] * A[p-1]) * (fact[N*M - k] * k) * ifac[p-k];
    //     f[k] += X[p] * Y[k] * Z[p-k];
    // }
    // debug(f);
    
    Mod ans = 0;
    for (int r = 0; r <= N; ++r) for (int c = 0; c <= M; ++c) if (r or c) {
        int k = r * M + c * N - r * c;
        Mod tmp = binom(N, r) * binom(M, c) * F[k];
        if ((r + c + 1) & 1) tmp = -tmp;
        ans += tmp;
    }
    print(ans.v);
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

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;
// #include <bits/extc++.h>
// #include <tr2/dynamic_bitset>

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

// template <size_t D, typename T> struct Vec : vector<Vec<D-1, T>> {
//     static_assert(D >= 1, "Vector dimension must be greater than zero!");
//     template <typename... Args> Vec(int n = 0, Args... args) : vector<Vec<D-1, T>>(n, Vec<D-1, T>(args...)) {}
// };

// template <typename T> struct Vec<1, T> : vector<T> {
//     Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {}
// };

template <typename T, typename U> istream& operator >> (istream &is, pair<T, U> &p)
{ return is >> p.first >> p.second; }

template <typename T, typename U> ostream& operator << (ostream &os, const pair<T, U> &p)
{ return os << p.first << " " << p.second; }

template <typename T> istream& operator >> (istream &is, vector<T> &vec)
{ for (size_t i = 0; i < size(vec); ++i) is >> vec[i]; return is; }

template <typename T> ostream& operator << (ostream &os, const vector<T> &vec)
{ for (size_t i = 0; i < size(vec); ++i) { if (i) os << " "; os << vec[i]; } return os; }

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
template <typename T> concept is_iterable = requires (T _t) { begin(_t); };

template <typename T> inline void _print_err(T &&_t);
template <typename T> inline void _print_err(T &&_t) requires is_iterable<T> and (not is_string<T>);
template <size_t I, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(const tuple<U...> &);
template <size_t I, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(const tuple<U...> &_t);
template <size_t I, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(tuple<U...> &);
template <size_t I, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(tuple<U...> &_t);

inline void _do() { cerr << "\n"; }
template <typename T> inline void _do(T &&_t) { _print_err(_t), cerr << "\n"; }
template <typename T, typename ...U> inline void _do(T &&_t, U &&..._u) { _print_err(_t), cerr << ", ", _do(_u...); }
#else
#define fastIO() cin.tie(0)->sync_with_stdio(0)
#define debug(...) void()
#define print(...) _P(__VA_ARGS__)
#endif

inline void _P() { cout << "\n"; }
template <typename T> inline void _P(T &&_t) { cout << _t << "\n"; }
template <typename T, typename ...U> inline void _P(T &&_t, U &&..._u) { cout << _t << " ", _P(_u...); }

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template <typename T, typename U> bool chmin(T &lhs, U rhs) { return lhs > rhs ? lhs = rhs, 1 : 0; }
template <typename T, typename U> bool chmax(T &lhs, U rhs) { return lhs < rhs ? lhs = rhs, 1 : 0; }

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

template <typename T> inline void _print_err(T &&_t) { cerr << _t; }

template <typename T> inline void _print_err(T &&_t) requires is_iterable<T> and (not is_string<T>) {
    _color.emplace_back(_color.back()), ++_color.back()[3];
    cerr << _color.back() << "[";
    for (bool _first = true; auto &_x : _t) {
        if (!_first) cerr << ", ";
        _print_err(_x), _first = false;
    }
    cerr << "]" << (_color.pop_back(), _color.back());
}

template <size_t I = 0, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(const tuple<U...> &) {
    cerr << ")" << (_color.pop_back(), _color.back());
}

template <size_t I = 0, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(const tuple<U...> &_t) {
    if (!I) {
        _color.emplace_back(_color.back()), ++_color.back()[3];
        cerr << _color.back();
    }
    cerr << (I ? ", " : "("), _print_err(get<I>(_t)), _print_err<I+1, U...>(_t);
}

template <size_t I = 0, typename ...U> inline typename enable_if<I == sizeof...(U), void>::type _print_err(tuple<U...> &) {
    cerr << ")" << (_color.pop_back(), _color.back());
}

template <size_t I = 0, typename ...U> inline typename enable_if<I <  sizeof...(U), void>::type _print_err(tuple<U...> &_t) {
    if (!I) {
        _color.emplace_back(_color.back()), ++_color.back()[3];
        cerr << _color.back();
    }
    cerr << (I ? ", " : "("), _print_err(get<I>(_t)), _print_err<I+1, U...>(_t);
}

#endif

#endif

/**
 *                                                                                                                 
 *                                                                                                                 
 *                                                                                                                 
 *                            iiiiii         iiiiiiiiii       iiiiiiiiiiiiii                                       
 *                       iiiiiiiiiiiii   iiiiiii    iiii    iiiiiiiiiiiiiii                          ii   iiii     
 *                    iiiiiiii     iiiiiiiii         iiii       iiii iii              iii          iiiiiiiiii      
 *                 iiiiiii          iiiiii           iiii    iiii   ii           iiiiiiiiii      iiii iiii         
 *               iiiiii            iiiii             iiii iiii        iii      iiii    iiiiiiiiiiiiiiiii  ii       
 *             iiiiii            iiiiiii            iiiiiii       iiiiiiii   iii    iiiiiiiiiiiiii iii  iiii       
 *           iiiiii             iiiiiii            iiiii   ii   iiii       iiiiiiiiiii iiii  iii iiii iiii      iii
 *          iiiii              iiiiiiii       ii        iiiii iiii    iiiiiiiii        iii iii  iii  iii  ii  iiii 
 *        iiiiii              iiiiiiii      iiiii     iiiii iiiiiiiiiiiiiiii         iii  iii  ii  iii  iii iiii   
 *       iiiii                 iiiiii     iiii     iiiiii iiiiiii    iii iii       iiii  ii   i   ii  iii  iii     
 *     iiiiii                            iiii  iiiiiiiiiiiiiii       iii iiii   iiiii  iii  ii  iii  iii  ii       
 *    iiiii                              iiiiiiii iiiiiiiiii       iiii   iiiiiiiii            ii  iii  ii         
 *   iiiii                                     iiiiii  iiii      iiiii              iii      ii   ii  i            
 * iiiiii                                  iiiiiiii   iiiii    iiiii                        ii  ii   ii            
 * iiiii                                iiii  iiii    iiiiiiiiiiii                             ii                  
 *  iii                              iiii   iiii       iiiiiiii                                                    
 *                                iiiii   iiii                                                                     
 *                              iiii     iiii                                                                      
 *                            iiii    iiiii                                                                        
 *                          iii     iiiii                                                                          
 *                        iii     iiiii                                                                            
 *                       iii   iiiiii                                                                              
 *                       iiiiiiiii                                                                                 
 *                       iiiiii                                                                                    
 *                                                                                                                 
 *                                                                                                                 
 *                                                                                                                 
**/
