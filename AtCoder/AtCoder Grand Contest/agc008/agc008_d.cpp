#pragma GCC optimize("O3", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

void solve() {
    int n; cin >> n;
    
    vector<pii> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i].X, --p[i].X, p[i].Y = i;
    sort(ALL(p));
    
    int fl = 1;
    vector<int> ans(n*n, -1);
    for (int i = 0; i < n; ++i) ans[p[i].X] = p[i].Y;
    for (int i = 0, tok = 0, lst = 0; i < n*n and tok < n and fl; ++i) {
        if (p[tok].X == i) {
            int tmp = p[tok].Y;
            while (tmp) {
                if (ans[lst] == -1) ans[lst] = p[tok].Y, --tmp;
                ++lst;
            }
            if (lst > i) fl = 0;
            ++tok;
        }
    }
    for (int i = n*n-1, tok = n-1, lst = n*n-1; i >= 0 and tok >= 0 and fl; --i) {
        if (p[tok].X == i) {
            int tmp = n - p[tok].Y - 1;
            while (tmp) {
                if (ans[lst] == -1) ans[lst] = p[tok].Y, --tmp;
                --lst;
            }
            if (lst < i) fl = 0;
            --tok;
        }
    }
    
    cout << (fl ? "Yes" : "No") << "\n";
    
    if (fl) {
        for (auto x : ans) cout << x+1 << " ";
        cout << "\n";
    }
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}