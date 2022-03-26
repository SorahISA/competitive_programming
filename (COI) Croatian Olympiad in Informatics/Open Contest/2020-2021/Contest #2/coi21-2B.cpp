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

vector<int> p;

int R(int x) {return x ^ p[x] ? p[x] = R(p[x]) : x;}
int U(int x, int y) {x = R(x), y = R(y); return x ^ y ? p[x] = y, 1 : 0;}

int dist(pii a1, pii a2) {
    return (a1.X - a2.X) * (a1.X - a2.X)
         + (a1.Y - a2.Y) * (a1.Y - a2.Y);
}

int32_t main() {
    fastIO();
    
    int n;
    cin >> n, p.resize(n+1), iota(ALL(p), 0);
    
    vector<pii> ant(n);
    for (auto &[x, y] : ant) cin >> x >> y;
    
    vector<pair<int, pii>> edge;
    
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            edge.eb(dist(ant[i], ant[j]), pii{i, j});
        }
    }
    sort(ALL(edge));
    
    int con = 1;
    for (auto eg : edge) {
        if ((con += U(eg.Y.X, eg.Y.Y)) == n) {
            cout << fixed << setprecision(8) << sqrt(eg.X) / 2 << "\n";
            return 0;
        }
    }
    
    cout << "0.00000000" << "\n";
    
    return 0;
}
