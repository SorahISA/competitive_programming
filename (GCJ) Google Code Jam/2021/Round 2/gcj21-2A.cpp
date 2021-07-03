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

void solve(int N) {
    int ret;
    for (int i = 1; i < N; ++i) {
        cout << "M " << i << " " << N << "\n" << flush;
        cin >> ret;
        if (ret != i) {
            cout << "S " << i << " " << ret << "\n" << flush;
            cin >> ret; assert(ret == 1);
        }
    }
    cout << "D\n" << flush;
    cin >> ret; assert(ret == 1);
    
    // int cost = 0;
    // for (int i = 2; i <= 100; ++i) cost += (100000000 - 1) / i + 1;
    // cout << cost << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1, n; cin >> t >> n;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve(n);
    }
    
    return 0;
}