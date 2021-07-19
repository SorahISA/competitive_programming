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

void solve() {
    // cout.fill(' ');
    // vector<int> min_len(50, 0);
    // min_len[0] = 1, min_len[1] = 1;
    // for (int i = 2; i < 50; ++i) {
        // min_len[i] = min_len[i-1] + min_len[i-2];
        // cout << setw(2) << i+1 << ": " << min_len[i] << "\n";
    // }
    
    int N; cin >> N;
    
    if (N >= 45) {
        /// must exist answer ///
        cin.ignore(), cin.ignore(INT_MAX, '\n');
        return cout << "YES\n", void();
    }
    
    vector<int> arr(N);
    for (auto &x : arr) cin >> x;
    sort(ALL(arr));
    
    for (int i = 2; i < N; ++i) {
        if (arr[i-2] + arr[i-1] > arr[i]) return cout << "YES\n", void();
    }
    cout << "NO\n";
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