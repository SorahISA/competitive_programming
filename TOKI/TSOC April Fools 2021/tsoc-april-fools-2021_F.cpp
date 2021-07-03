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

const int maxn = 100 + 5;

int adj[maxn][3];

string arr[] = {
    ".-",
    "-...",
    "-.-.",
    "-..",
    ".",
    "..-.",
    "--.",
    "....",
    "..",
    ".---",
    "-.-",
    ".-..",
    "--",
    "-.",
    "---",
    ".--.",
    "--.-",
    ".-.",
    "...",
    "-",
    "..-",
    "...-",
    ".--",
    "-..-",
    "-.--",
    "--..",
};

void solve() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, t; cin >> u >> v >> t;
        adj[u][t] = v;
    }
    
    string s; cin >> s;
    int now = 1, fl = 1;
    for (auto c : s) {
        for (auto x : arr[c-'A']) {
            // cout << c << " " << arr[c-'A'] << "\n";
            if (x == '.') {
                if (adj[now][1]) now = adj[now][1];
                else fl = 0;
            }
            if (x == '-') {
                if (adj[now][2]) now = adj[now][2];
                else fl = 0;
            }
        }
    }
    cout << (fl ? now : -1) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}