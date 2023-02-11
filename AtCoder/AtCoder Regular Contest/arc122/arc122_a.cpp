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

const int mod = 1E9 + 7;

void solve() {
    int N; cin >> N;
    
    vector<int> arr(N);
    for (auto &x : arr) cin >> x;
    
    vector<int> fib(N+1); fib[0] = fib[1] = 1;
    for (int i = 2; i <= N; ++i) fib[i] = (fib[i-1] + fib[i-2]) % mod;
    
    int ans = arr[0] * fib[N] % mod;
    for (int i = 0; i < N-1; ++i) {
        // cout << fib[i] << " " << fib[N-2-i] << "\n";
        ans += arr[i+1] * (fib[N] - 2 * fib[i] * fib[N-2-i] % mod) % mod;
    }
    cout << (ans % mod + mod) % mod << "\n";
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