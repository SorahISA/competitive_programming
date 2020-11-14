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

const int INF = 1E18;

int R(int x, int y) {
    if (x < y) swap(x, y);
    if (y == 1) return x;
    return R(x / y, y);
}

void solve() {
    int g, h, ph, a, b;
    cin >> g >> h, ph = 1;
    
    while (ph *= h) {
        int x = (ph - 1) / g + 1;
        if (g * x < 2 * ph) {
            b = g * x;
            a = h * g * x + (x != 1) * g;
            // break;
            /// also got AC but not sure if it's safe to be removed ///
            if (R(a, b) == h) break;
        }
        if (ph > INF / h) assert(0);
    }
    
    cout << a << " " << b << "\n";
}

int32_t main() {
    fastIO();
    
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
