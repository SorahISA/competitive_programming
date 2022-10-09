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

template<class T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) os << vec[i] << " ";
    return os;
}

int mp[30][30];
string ans, maxAns;

int dfs(int now) {
    ans.push_back(now + 'a');
    if (ans.size() >= 39) {maxAns = ans; return 1;}
    if (ans.size() > maxAns.size()) maxAns = ans;
    
    for (int i = 0; i < 26; ++i) {
        if (!mp[now][i] and dfs(i)) return 1;
    }
    ans.pop_back();
    return 0;
}

void solve() {
    memset(mp, 0x00, sizeof(mp));
    ans = maxAns = "";
    
    int n; cin >> n;
    
    for (int i = 0; i < n; ++i) {
        string s; cin >> s;
        mp[s[0]-'a'][s[1]-'a'] = 1;
    }
    
    for (int i = 0; i < 26; ++i) {
        if (dfs(i)) break;
    }
    
    for (int i = 0; i < maxAns.size()+1>>1; ++i) {
        cout << maxAns.substr(i, maxAns.size()+1>>1) << "\n";
    }
}

int32_t main(int32_t argc, char *argv[]) {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}