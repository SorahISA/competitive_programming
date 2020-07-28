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
    
    vector<string> str(q + 1);
    str[0] = s;
    for (int i = 1; i <= q; ++i) {
        cin >> op, str[i] = str[i - 1];
        if (op == "toggle") {
            cin >> x, --x;
            str[i][x] ^= 1;
        }
        if (op == "query") {
            cin >> l >> r, --l, --r;
            int cnt = 0;
            for (int j = 0; j < i; ++j) {
                int fl = 1;
                for (int idx = l; idx < r; ++idx) fl &= (str[j][idx] ^ '0');
                cnt += fl;
            }
            cout << cnt << "\n";
        }
    }
    
    return 0;
}