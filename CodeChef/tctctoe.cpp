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
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << "\n";
        os << vec[i];
    }
    return os;
}

int CheckWinner(vector<string> &s) { /// (-1, 0, 1, 2) |-> (invalid, null, X, O)
    int cntX = 0, cntO = 0;
    for (int i = 0; i < 9; ++i) {
        cntX += s[i/3][i%3] == 'X';
        cntO += s[i/3][i%3] == 'O';
    }
    // cout << s << "\n" << cntX << " " << cntO << "\n";
    if (cntX > cntO + 1 or cntX < cntO) return -1;
    
    for (int i = 0; i < 3; ++i) {
        int cx = 0, cy = 0;
        for (int j = 0; j < 3; ++j) {
            cx += s[i][j] == 'X';
            cy += s[i][j] == 'O';
        }
        if (max(cx, cy) == 3) return cx == 3 ? 1 : 2;
    }
    
    for (int j = 0; j < 3; ++j) {
        int cx = 0, cy = 0;
        for (int i = 0; i < 3; ++i) {
            cx += s[i][j] == 'X';
            cy += s[i][j] == 'O';
        }
        if (max(cx, cy) == 3) return cx == 3 ? 1 : 2;
    }
    
    if (s[0][0] == 'X' and s[1][1] == 'X' and s[2][2] == 'X') return 1;
    if (s[0][2] == 'X' and s[1][1] == 'X' and s[2][0] == 'X') return 1;
    if (s[0][0] == 'O' and s[1][1] == 'O' and s[2][2] == 'O') return 2;
    if (s[0][2] == 'O' and s[1][1] == 'O' and s[2][0] == 'O') return 2;
    
    return 0;
}

void solve() {
    vector<string> s(3);
    for (auto &str : s) cin >> str;
    
    if (CheckWinner(s) == -1) return cout << 3 << "\n", void();
    
    int full = 1;
    for (int i = 0; i < 9; ++i) full &= s[i/3][i%3] != '_';
    
    int winner = 0, null = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            char tmp = s[i][j];
            s[i][j] = '_';
            int ret = CheckWinner(s);
            s[i][j] = tmp;
            // cout << ret << "\n";
            if (ret == -1) continue;
            if (winner and ret and ret != winner) return cout << 3 << "\n", void();
            if (ret) winner = ret;
            else ++null;
        }
    }
    if (!null)               cout << 3 << "\n";
    else if (winner or full) cout << 1 << "\n";
    else                     cout << 2 << "\n";
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