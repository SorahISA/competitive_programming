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

void solve() {
    int C; cin >> C;
    
    vector<int> B(C);
    for (auto &x : B) cin >> x;
    
    if (!B.front() or !B.back()) return cout << "IMPOSSIBLE\n", void();
    
    deque<string> vec(C-1, string(C, '.'));
    
    for (int i = 0, sum = 0, lst = 0; i < C; ++i) {
        if (!B[i]) continue;
        for (int row = 0, col = sum; col < i; ++row, ++col) vec[row][col] = '\\';
        sum += B[i];
        for (int row = 0, col = sum-1; col > i; ++row, --col) vec[row][col] = '/';
    }
    
    while (vec.size() >= 2 and vec[vec.size()-2] == string(C, '.')) vec.pop_back();
    assert(vec.back() == string(C, '.'));
    cout << vec.size() << "\n" << vec << "\n";
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

/*
14
2 1 1
3 1 0 2
3 1 1 1
3 2 0 1
4 1 0 0 3
4 1 0 1 2
4 1 0 2 1
4 1 1 0 2
4 1 1 1 1
4 1 2 0 1
4 2 0 0 2
4 2 0 1 1
4 2 1 0 1
4 3 0 0 1
*/