#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ef push_front
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define SZ(x) ((int)(x).size())

#ifdef local
#define debug(...) \
    cerr << "\u001b[33m" << "LINE " << __LINE__ << ": (" << #__VA_ARGS__ << ") = ",\
    _do(__VA_ARGS__),\
    cerr << "\u001b[0m"
#define fastIO()
template <typename T> void _do(T &&_t) {cerr << _t << "\n";}
template <typename T, typename ...U> void _do(T &&_t, U &&..._u) {cerr << _t << ", "; _do(_u...);}
#else
#define debug(...) void()
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)
#endif

// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// inline int getRand(int L, int R) {
    // if (L > R) swap(L, R);
    // return (int)(rng() % ((uint64_t)R - L + 1) + L);
// }

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < SZ(vec); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    int N, M, T; cin >> N >> M >> T;
    
    vector<int> tim(N);
    for (int &x : tim) {
        string S; cin >> S;
        x = 3600 * stoi(S.substr(0, 2))
          +   60 * stoi(S.substr(3, 2))
          +    1 * stoi(S.substr(6, 2));
    }
    
    vector<pii> rng(N);
    for (int i = 0; i < N; ++i) {
        rng[i].X = lower_bound(ALL(tim), tim[i]) - begin(tim);
        rng[i].Y = lower_bound(ALL(tim), tim[i] + T) - begin(tim) - 1;
    }
    
    int flag = 0;
    vector<int> ans(N, 0);
    ans[0] = 1;
    for (int i = 0; i < N; ++i) {
        if (!ans[rng[i].X]) ans[rng[i].X] = ans[rng[i].X-1] + 1;
        int cnt = -1, left = -1;
        for (int j = rng[i].Y; j >= rng[i].X; --j) {
            if (ans[j]) {
                cnt = ans[j] - ans[rng[i].X] + 1;
                left = rng[i].Y - j;
                break;
            }
        }
        flag |= cnt + left >= M;
        while (left) {
            int j = rng[i].Y - left + 1;
            ans[j] = ans[j-1] + (cnt < M);
            cnt += cnt < M, --left;
        }
    }
    
    if (!flag) cout << "No solution\n";
    else {
        cout << ans.back() << "\n";
        for (int x : ans) cout << x << "\n";
    }
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
