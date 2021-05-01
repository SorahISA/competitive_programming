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
        os << vec[i];
    }
    return os;
}

void solve() {
    string s; cin >> s;
    
    int fl = 1;
    deque<char> str;
    for (auto c : s) {
        if (c == 'R') fl ^= 1;
        else fl ? str.push_back(c) : str.push_front(c);
        if (str.size() >= 2 and str[0] == str[1]) str.pop_front(), str.pop_front(); 
        if (str.size() >= 2 and str[str.size()-1] == str[str.size()-2]) str.pop_back(), str.pop_back(); 
    }
    
    if (!fl) reverse(ALL(str));
    cout << str << "\n";
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