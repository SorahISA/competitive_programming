#pragma GCC optimize("Ofast", "unroll-loops")

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
#define ALL(x) x.begin(), x.end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0)

int32_t main() {
    fastIO();
    
    map<char, pii> pl;
    int h, w, n;
    char tmp;
    cin >> h >> w >> n;
    
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cin >> tmp;
            if (tmp != '0') pl[tmp] = pii{i, j};
        }
    }
    
    if (pl.size() < n) return cout << "Mission fail.\n", 0;
    
    for (auto x : pl) {
        if (n-- == 0) break;
        cout << x.Y.X << " " << x.Y.Y << "\n";
    }
    
    return 0;
}
