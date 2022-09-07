#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define eb emplace_back
#define pb pop_back
#define X first
#define Y second
#ifdef local
#define debug(...) do{\
    fprintf(stderr, "LINE %d: (%s) = ", __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template <typename T> void _do(T &&_x) {cerr << _x << endl;}
template <typename T, typename ...S> void _do(T &&_x, S &&..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs){return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs){return lhs < rhs ? lhs = rhs, 1 : 0;}

void solve() {
    vector<string> tr1{""}, tr2{""};
    
    string str;
    int dep = 0;
    char ch;
    
    do {
        cin >> ch;
             if (ch == '[') ++dep;
        else if (ch == ']') --dep, str.pb();
        else                tr1.eb(str += ch);
    } while (dep > 0);
    
    do {
        cin >> ch;
             if (ch == '[') ++dep;
        else if (ch == ']') --dep, str.pb();
        else                tr2.eb(str += ch);
    } while (dep > 0);
    
    /// find LCS ///
    
    int sz1 = SZ(tr1), sz2 = SZ(tr2);
    vector<vector<int>> lcs(sz1, vector<int>(sz2, 0));
    
    // for (int i = 0; i < sz1; ++i) debug(tr1[i]);
    // for (int i = 0; i < sz2; ++i) debug(tr2[i]);
    
    for (int i = 1; i < sz1; ++i) {
        for (int j = 1; j < sz2; ++j) {
            lcs[i][j] = max({
                lcs[i-1][j],
                lcs[i][j-1],
                lcs[i-1][j-1] + (tr1[i] == tr2[j])
            });
        }
    }
    
    cout << lcs[sz1-1][sz2-1] << "\n";
}

signed main() {
    IOS();
    int _ = 1;
    // cin >> _;
    for (int i=1;i<=_;++i) {
        solve();
    }
}
