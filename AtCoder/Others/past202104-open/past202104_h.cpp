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
#define pb pop_back
#define ef push_front
#define pf pop_front
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template <typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int INF = LLONG_MAX;

inline int divceil(int x, int y) {
    if (x % y == 0) return x / y;
    return (x - 1) / y + 1;
}

void solve() {
    int N, M, K, Q; cin >> N >> M >> K >> Q;
    
    vector<int> tp_0{0}, tp_1{0};
    for (int i = 0, p, t; i < N; ++i) {
        cin >> p >> t;
             if (t == 0) tp_0.eb(p);
        else if (t == 1) tp_1.eb(p);
    }
    sort(ALL(tp_0)), sort(ALL(tp_1));
    partial_sum(ALL(tp_0), begin(tp_0)), partial_sum(ALL(tp_1), begin(tp_1));
    
    int ans = INF;
    for (int i = 0, j = M; i <= M; ++i, --j) {
        if (SZ(tp_0) <= i or SZ(tp_1) <= j) continue;
        // cerr << tp_0[i] << " + " << tp_1[j] << " + " << Q << " * " << divceil(j, K) << "\n";
        chmin(ans, tp_0[i] + tp_1[j] + Q * divceil(j, K));
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}
