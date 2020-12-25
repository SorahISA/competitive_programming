#pragma GCC optimize("Ofast", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

const int INF = 2E9 + 5;
const int m1 = 1000000007;
const int m2 =  998244353;

namespace Subtask2 {

void solve(int n, int ans = 1) {
    vector<pii> cow(n);
    for (auto &x : cow) cin >> x.X >> x.Y;
    sort(ALL(cow));
    
    for (int i = 1; i < (1<<n); ++i) {
        int minX = INF, maxX = -INF, minY = INF, maxY = -INF;
        for (int j = 0; j < n; ++j) {
            if (i >> j & 1) {
                minX = min(minX, cow[j].X), maxX = max(maxX, cow[j].X);
                minY = min(minY, cow[j].Y), maxY = max(maxY, cow[j].Y);
            }
        }
        int r = max(maxX - minX, maxY - minY);
        if (maxX - minX >= maxY - minY) {
            /// (minX, y), (maxX, y+r) ///
            int minY_available = -INF, maxY_available = INF;
            for (int j = 0; j < n; ++j) {
                if (~i >> j & 1) {
                    if (minX <= cow[j].X and cow[j].X <= maxX) {
                        if (cow[j].Y < minY) minY_available = max(minY_available, cow[j].Y + 1);
                        else                 maxY_available = min(maxY_available, cow[j].Y - 1);
                    }
                }
            }
            if (minY_available <= minY and maxY <= maxY_available and maxY_available - minY_available >= r) ++ans;
        }
        else if (maxX - minX <= maxY - minY) {
            /// (x, minY), (x+r, maxY) ///
            int minX_available = -INF, maxX_available = INF;
            for (int j = 0; j < n; ++j) {
                if (~i >> j & 1) {
                    if (minY <= cow[j].Y and cow[j].Y <= maxY) {
                        if (cow[j].X < minX) minX_available = max(minX_available, cow[j].X + 1);
                        else                 maxX_available = min(maxX_available, cow[j].X - 1);
                    }
                }
            }
            if (minX_available <= minX and maxX <= maxX_available and maxX_available - minX_available >= r) ++ans;
        }
        // printf("%I64d: %I64d, min: (%I64d, %I64d), max: (%I64d, %I64d)\n", i, ans, minX, minY, maxX, maxY);
    }
    
    cout << ans << "\n";
}

} /// End of Subtask2

pii fastpow(int b1, int exp) {
    int b2 = b1, a1 = 1, a2 = 1;
    while (exp) {
        if (exp & 1) a1 = a1 * b1 % m1, a2 = a2 * b2 % m2;
        b1 = b1 * b1 % m1, b2 = b2 * b2 % m2;
        exp >>= 1;
    }
    return {a1, a2};
}

void turn_on(pii &val, int idx) {
    pii add = fastpow(2, idx);
    val.X = (val.X + add.X) % m1;
    val.Y = (val.Y + add.Y) % m2;
}

void turn_off(pii &val, int idx) {
    pii sub = fastpow(2, idx);
    val.X = (val.X - sub.X + m1) % m1;
    val.Y = (val.Y - sub.Y + m2) % m2;
}

void solve() {
    int n; cin >> n;
    
    // if (n <= 20) {Subtask2::solve(n); return;}
    
    vector<pii> cow(n);
    for (auto &x : cow) cin >> x.X >> x.Y;
    sort(ALL(cow));
    
    vector<pii> ans;
    
    for (int L = 0; L < n; ++L) {
        for (int R = L; R < n; ++R) {
            int r = max(abs(cow[R].X - cow[L].X), abs(cow[R].Y - cow[L].Y));
            int minX = cow[L].X, maxX = cow[R].X;
            int minY = min(cow[L].Y, cow[R].Y), maxY = max(cow[L].Y, cow[R].Y);
            
            vector<pii> vec;
            if (maxX - minX >= maxY - minY) {
                /// (minX, y), (maxX, y+r) ///
                for (int i = 0; i < n; ++i) {
                    if (minX <= cow[i].X and cow[i].X <= maxX) vec.eb(cow[i].Y, i);
                }
            }
            else if (maxX - minX <= maxY - minY) {
                /// (x, minY), (x+r, maxY) ///
                for (int i = 0; i < n; ++i) {
                    if (minY <= cow[i].Y and cow[i].Y <= maxY) vec.eb(cow[i].X, i);
                }
            }
            sort(ALL(vec));
            
            int sz = vec.size();
            pii state{0, 0};
            for (int tokL = 0, tokR = 0; tokR < sz; ++tokR) {
                while (vec[tokL].X < vec[tokR].X - r) {
                    turn_off(state, vec[tokL].Y);
                    if (vec[tokL].X + 1 < vec[tokR].X - r) ans.eb(state);
                    ++tokL;
                }
                turn_on(state, vec[tokR].Y), ans.eb(state);
                if (tokR == sz - 1) {
                    while (tokL < sz) turn_off(state, vec[tokL++].Y), ans.eb(state);
                }
            }
        }
    }
    
    sort(ALL(ans));
    ans.resize(unique(ALL(ans)) - ans.begin());
    
    cout << ans.size() << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
