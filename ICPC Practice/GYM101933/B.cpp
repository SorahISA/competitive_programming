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
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &x, T y) {return x > y ? x = y, 1 : 0;}
template<typename T> bool chmax(T &x, T y) {return x < y ? x = y, 1 : 0;}

const int INF = INT_MAX;

inline void AC() {cout << "makes sense\n";}
inline void WA() {cout << "something is fishy\n";}

void solve() {
    int N; cin >> N;
    
    int flag = -1;
    vector<int> num(N, INF);
    for (int i = 0; i < N; ++i) {
        string str; cin >> str;
        if (str != "mumble") num[i] = stoi(str), flag = i;
    }
    
    if (flag == -1) return AC();
    if (num[flag] - flag < 1) return WA();
    
    for (int i = 0; i < N; ++i) {
        if (num[i] != INF and num[i] != num[flag] + (i - flag)) return WA();
    }
    AC();
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}