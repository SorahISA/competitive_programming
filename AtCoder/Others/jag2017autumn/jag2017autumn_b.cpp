#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T> using Prior = std::priority_queue<T>;
template<typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &x, T y) {return x > y ? x = y, 1 : 0;}
template<typename T> bool chmax(T &x, T y) {return x < y ? x = y, 1 : 0;}

string S;
vector<int> wins(26, 0);

int recur(int lp, int rp) {
    // cout << lp << " " << rp << "\n";
    if (lp == rp) return S[lp] - 'a';
    for (int i = lp, lay = 0; i <= rp; ++i) {
        if (S[i] == '[') ++lay;
        if (S[i] == ']') --lay;
        if (lay == 1 and S[i] == '-') {
            int winL = recur(lp+1, i-1), winR = recur(i+1, rp-1);
            // cout << winL << "-" << winR << "\n";
            return wins[winL] ? (--wins[winL], winL) : (--wins[winR], winR);
        }
    }
    return -1;
}

void solve() {
    cin >> S;
    int N = (SZ(S) + 3) / 4;
    
    for (int i = 0; i < N; ++i) {
        char c; int x; cin >> c >> x;
        wins[c - 'a'] = x;
    }
    
    recur(0, SZ(S) - 1);
    
    for (int i = 0; i < 26; ++i) {
        if (wins[i]) return cout << "No\n", void();
    }
    cout << "Yes\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}