#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

int32_t main() {
    fastIO();
    
    int n, q, x, l, r;
    string s, op;
    cin >> n >> q >> s;
    
    vector<int> ans(n, 0), lst_mod(n, 0);
    
    for (int i = 1; i <= q; ++i) {
        cin >> op;
        if (op == "toggle") {
            cin >> x, --x;
            if (s[x] == '1') ans[x] += i - lst_mod[x];
            s[x] ^= 1, lst_mod[x] = i;
        }
        if (op == "query") {
            cin >> l >> r, --l, --r;
            cout << ans[l] + (s[l] ^ '0') * (i - lst_mod[l]) << "\n";
        }
    }
    
    return 0;
}