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
#define pb pop_back
#define pf pop_front
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int maxn = 1000 + 5;
const int dx[] = {1, 0, -1,  0};
const int dy[] = {0, 1,  0, -1};

int chosen[maxn][maxn];

void solve() {
    int N, M; cin >> N >> M;
    
    vector<pair<int, pii>> num; /// (val, (x, y))
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            int tmp; cin >> tmp, num.eb(tmp, pii{i, j});
        }
    }
    sort(ALL(num));
    
    int ans = 0;
    for (auto [val, p] : num) {
        int mul = 1;
        for (int d = 0; d < 4; ++d) {
            mul += chosen[p.X+dx[d]][p.Y+dy[d]];
        }
        ans += mul * val, chosen[p.X][p.Y] = 1;
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