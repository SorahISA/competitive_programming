#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

int32_t main() {
    fastIO();
    
    string s;
    cin >> s;
    
    int ans = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (i % 3 == 0) ans += s[i] != 'p' and s[i] != 'P';
        if (i % 3 == 1) ans += s[i] != 'e' and s[i] != 'E';
        if (i % 3 == 2) ans += s[i] != 'r' and s[i] != 'R';
    }
    cout << ans << "\n";
    
    return 0;
}