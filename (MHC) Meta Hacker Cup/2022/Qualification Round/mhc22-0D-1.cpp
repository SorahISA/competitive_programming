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

const int maxn = 200'005;

void solve() {
    map<pii, int64_t> answer;
    
    int N, M, Q; cin >> N >> M >> Q;
    
    vector<pii> adj[N];
    map<pii, int> edges;
    
    for (int i = 0, a, b, c; i < M; ++i) {
        cin >> a >> b >> c, --a, --b;
        if (a > b) swap(a, b);
        adj[a].eb(b, c), adj[b].eb(a, c);
        edges.ee(pii{a, b}, c);
    }
    
    for (int i = 0; i < N; ++i) sort(ALL(adj[i]));
    
    /// build adj bitset for vertecies with 2*sqrt(N) largest degree ///
    
    int large = min(2 * (int)ceil(sqrt(N)), N);
    bitset<maxn> adj_large[large];
    
    vector<int> deg_id(N);
    iota(ALL(deg_id), 0);
    sort(ALL(deg_id), [&](int x, int y) {return SZ(adj[x]) > SZ(adj[y]);});
    
    vector<int> is_large(N, -1); /// -1 for small; >= 0 for index in `adj_large`
    for (int i = 0; i < large; ++i) {
        int id = deg_id[i];
        is_large[id] = i;
        for (auto [to, cost] : adj[id]) adj_large[i][to] = 1;
    }
    
    /// query ///
    
    for (int _ = 1, x, y; _ <= Q; ++_) {
        cin >> x >> y, --x, --y;
        if (x > y) swap(x, y);
        
        auto it = answer.find({x, y});
        if (it != answer.end()) {
            cout << it->second << " \n"[_ == Q];
            continue;
        }
        
        auto it_edge = edges.find({x, y});
        int64_t cnt = 2 * (it_edge != edges.end() ? it_edge->second : 0);
        if (SZ(adj[x]) > SZ(adj[y])) swap(x, y); /// let `x` be the vertex with smaller degree
        
        if (is_large[y] >= 0) {
            auto &adj_y = adj_large[is_large[y]];
            for (auto [to, cost] : adj[x]) {
                if (adj_y[to]) cnt += min(cost, edges[{min(y, to), max(y, to)}]);
            }
        }
        else {
            int tok_y = 0;
            for (auto [to, cost] : adj[x]) {
                while (tok_y < SZ(adj[y]) and adj[y][tok_y].first < to) ++tok_y;
                if (tok_y == SZ(adj[y])) break;
                if (adj[y][tok_y].first == to) cnt += min(cost, adj[y][tok_y].second);
            }
        }
        
        answer[{min(x, y), max(x, y)}] = cnt;
        cout << cnt << " \n"[_ == Q];
    }
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
