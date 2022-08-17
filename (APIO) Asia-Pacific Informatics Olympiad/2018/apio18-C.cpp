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

const int maxn = 1E5 + 5;

vector<int> adj[maxn], dfn, low;
vector<int> bct[2*maxn];
deque<int> stk;

void Tarjan(int now, int &tok_dfn, int &tok_bcc) {
    dfn[now] = low[now] = tok_dfn++;
    stk.eb(now);
    for (int x : adj[now]) {
        if (!~dfn[x]) {
            Tarjan(x, tok_dfn, tok_bcc);
            chmin(low[now], low[x]);
            // debug(now, x, dfn[now], low[x], stk);
            if (low[x] >= dfn[now]) {
                int p;
                while ((p = stk.back()) != x) {
                    bct[p].eb(tok_bcc), bct[tok_bcc].eb(p), stk.pb();
                }
                bct[p].eb(tok_bcc), bct[tok_bcc].eb(p), stk.pb();
                bct[now].eb(tok_bcc), bct[tok_bcc].eb(now);
                ++tok_bcc;
            }
        }
        chmin(low[now], dfn[x]);
    }
    // debug(now, dfn[now], low[now]);
}

void solve() {
    int N, M; cin >> N >> M;
    
    for (int i = 0, u, v; i < M; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].eb(v), adj[v].eb(u);
    }
    
    dfn.assign(N, -1), low.resize(N);
    
    int tok_bcc = N;
    for (int i = 0, tok_dfn = 0; i < N; ++i) {
        if (!~dfn[i]) stk.clear(), Tarjan(i, tok_dfn, tok_bcc);
    }
    
    // for (int i = N; i < tok_bcc; ++i) debug(i, bct[i]);
    
    /// calculate answer in Block-Cut Tree ///
    
    vector<int> vis(tok_bcc, 0), sz(tok_bcc, 0);
    
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        if (vis[i]) continue;
        
        auto get_sz_ = [&](auto &&get_sz, int now, int fa) -> void {
            vis[now] = true, sz[now] = (now < N);
            for (int x : bct[now]) {
                if (x == fa) continue;
                get_sz(get_sz, x, now), sz[now] += sz[x];
            }
        };
        get_sz_(get_sz_, i, -1);
        
        int sz_all = sz[i];
        ans += sz_all * (sz_all - 1) * (sz_all - 2);
        
        auto dfs_ = [&](auto &&dfs, int now, int fa) -> void {
            for (int x : bct[now]) {
                if (x == fa) continue;
                dfs(dfs, x, now);
                if (now >= N) ans -= (SZ(bct[now]) - 1) * sz[x] * (sz[x] - 1);
            }
            if (now >= N) ans -= (SZ(bct[now]) - 1) * (sz_all - sz[now]) * (sz_all - sz[now] - 1);
        };
        dfs_(dfs_, i, -1);
    }
    cout << ans << "\n";
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
