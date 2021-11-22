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
#define pf pop_front
#define pb pop_back
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
    string state; cin >> state;
    
    int remain_A[] = {4, 4, 3, 3, 2, 2, 1, 1, 0, 0};
    int remain_B[] = {5, 4, 4, 3, 3, 2, 2, 1, 1, 0};
    
    int min_A = 0, max_A = 0, min_B = 0, max_B = 0;
    for (int i = 0; i < 10; ++i) {
        if (~i & 1) {
            if (state[i] == '1') ++min_A, ++max_A;
            if (state[i] == '?') ++max_A;
        }
        else {
            if (state[i] == '1') ++min_B, ++max_B;
            if (state[i] == '?') ++max_B;
        }
        if (min_A + remain_A[i] < max_B) return cout << i+1 << "\n", void();
        if (min_B + remain_B[i] < max_A) return cout << i+1 << "\n", void();
    }
    cout << 10 << "\n";
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