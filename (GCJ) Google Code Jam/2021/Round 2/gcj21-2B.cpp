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
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % (uint64_t)(R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, deque<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << "\n";
        os << vec[i];
    }
    return os;
}

const int maxloop = 1000000;
const int maxn = maxloop + 5;

vector<int> ways(maxn, 0);

void init() {
    for (int i = 2; i <= maxloop; ++i) {
        ways[i] = 1;
        for (int k = 2; k*k <= i; ++k) {
            if (i % k == 0) {
                ways[i] = max(ways[i], ways[i/k-1] + 1);
                ways[i] = max(ways[i], ways[k-1]   + 1);
            }
        }
    }
}

void solve() {
    int N; cin >> N;
    int ans = 1;
    for (int k = 3; k <= N; ++k) {
        if (N % k == 0) ans = max(ans, ways[N/k-1] + 1);
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    init();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}