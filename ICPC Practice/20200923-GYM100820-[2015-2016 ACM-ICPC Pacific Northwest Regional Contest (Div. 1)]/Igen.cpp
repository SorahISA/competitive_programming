#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb push_back
#define ALL(x) (x).begin(), (x).end()
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

const int INF = 1E18;

int32_t main() {
    freopen("Iin.txt", "w", stdout);
    fastIO();
    srand(time(NULL));
    
    int n = 30;
    cout << n << "\n";
    
    vector<pair<int, int>> pt;
    for (int i = 0; i < n; ++i) {
        int x = rand() % 10000, y = rand() % 10000, fl = 1;
        for (auto [_x, _y] : pt) {
            if ((_x - x) * (_x - x) + (_y - y) * (_y - y) < 10000) {
                fl = 0; break;
            }
        }
        if (fl) {
            pt.eb(x, y);
            cout << x/1000 << "." << setw(3) << setfill('0') << x%1000 << " ";
            cout << y/1000 << "." << setw(3) << setfill('0') << y%1000 << "\n";
        }
        else --i;
    }
    
    return 0;
}