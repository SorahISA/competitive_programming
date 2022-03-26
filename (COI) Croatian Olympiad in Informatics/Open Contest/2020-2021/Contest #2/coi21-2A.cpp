#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template <typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

int32_t main() {
    fastIO();
    
    int n, minV = 0, maxV = -1, nowV = 0;
    string s;
    cin >> n >> s;
    
    for (auto c : s) {
        if (c == '+') maxV = max(maxV, nowV++);
        if (c == '-') minV = min(minV, --nowV);
        if (c == '=') maxV = max(maxV, nowV), minV = min(minV, nowV);
    }
    
    vector<string> mat(maxV - minV + 1, string(n, '.'));
    
    nowV = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '+') mat[nowV++ - minV][i] = '/';
        if (s[i] == '-') mat[--nowV - minV][i] = '\\';
        if (s[i] == '=') mat[nowV   - minV][i] = '_';
    }
    reverse(ALL(mat));
    
    for (auto str : mat) cout << str << "\n";
    
    return 0;
}
