#ifndef SorahISA
#define SorahISA
#include SorahISA __FILE__ SorahISA

const int lgmx = 30;

struct Trie {
    
    vector<array<int, 2>> ch;
    vector<int> cnt;
    int size, bitlen;
    int root = 0;
    
    void init(int C) {
        bitlen = C;
        size = 0;
        ch.clear(), cnt.clear();
        root = new_node();
    }
    
    int new_node() {
        ch.eb(array<int, 2>{-1, -1}), cnt.eb(0);
        return size++;
    }
    
    void add(int val, int occ = 1) {
        int now = root;
        cnt[now] += occ;
        for (int b = bitlen-1; b >= 0; --b) {
            if (ch[now][val>>b&1] == -1) ch[now][val>>b&1] = new_node();
            now = ch[now][val>>b&1];
            cnt[now] += occ;
        }
    }
    
    int max_xor(int val) {
        int now = root, ans = 0;
        for (int b = bitlen-1; b >= 0; --b) {
            if (ch[now][~val>>b&1] != -1 and cnt[ch[now][~val>>b&1]]) {
                ans |= int(1) << b;
                now = ch[now][~val>>b&1];
            }
            else {
                now = ch[now][val>>b&1];
            }
        }
        return ans;
    }
    
};

void solve() {
    int N; cin >> N;
    
    vector<int> A(N);
    for (int &x : A) cin >> x;
    
    vector<int> S(N+1, 0);
    for (int i = N-1; i >= 0; --i) S[i] = S[i+1] ^ A[i];
    
    Trie trie; trie.init(lgmx);
    for (int i = 0; i < N; ++i) trie.add(S[i], 1);
    
    int root = -1;
    vector<int> par(N, -1), lc(N, -1), rc(N, -1);
    {
        stack<int> stk;
        for (int i = 0; i < N; ++i) {
            int lst = -1;
            while (SZ(stk) and A[i] > A[stk.top()]) lst = stk.top(), stk.pop();
            if (SZ(stk)) par[i] = stk.top();
            if (lst != -1) par[lst] = i;
            stk.ee(i);
        }
        
        for (int i = 0; i < N; ++i) {
            if (par[i] == -1) root = i;
            if (par[i] != -1 and i < par[i]) lc[par[i]] = i;
            if (par[i] != -1 and par[i] < i) rc[par[i]] = i;
        }
    }
    
    int ans = 0;
    
    function<void(int, int, int)> recur = [&](int now, int l, int r) {
        // debug(now, l, r);
        /// trie contains S[l ... r] (add S[r+1] when needed) ///
        /// query max (S[l'] xor S[now] xor S[now+1] xor S[r']) ///
        ///     for l <= l' <= now and now + 1 <= r' <= r + 1 ///
        if (l == r) {
            trie.add(S[l], -1);
        }
        else if (now - l < r - now) {
            /// use S[l ... now] to ask S[now+1 ... r+1] ///
            for (int i = l; i <= now; ++i) trie.add(S[i], -1);
            trie.add(S[r+1], 1);
            for (int i = l; i <= now; ++i) chmax(ans, trie.max_xor(S[i] ^ A[now]));
            trie.add(S[r+1], -1);
            if (rc[now] != -1) recur(rc[now], now + 1, r);
            for (int i = l; i <= now-1; ++i) trie.add(S[i], 1);
            if (lc[now] != -1) recur(lc[now], l, now - 1);
        }
        else {
            /// use S[now+1 ... r+1] to ask S[l ... now] ///
            for (int i = now; i <= r; ++i) trie.add(S[i], -1);
            trie.add(S[now], 1);
            for (int i = now; i <= r; ++i) chmax(ans, trie.max_xor(S[i+1] ^ A[now]));
            trie.add(S[now], -1);
            if (lc[now] != -1) recur(lc[now], l, now - 1);
            for (int i = now+1; i <= r; ++i) trie.add(S[i], 1);
            if (rc[now] != -1) recur(rc[now], now + 1, r);
        }
    };
    recur(root, 0, N-1);
    
    print(ans);
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
