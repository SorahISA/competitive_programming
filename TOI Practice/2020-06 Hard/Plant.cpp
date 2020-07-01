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
    
    int n, L;
    cin >> L >> n;
    
    vector<pii> plant(n);
    for (auto &x : plant) cin >> x.X >> x.Y;
    sort(ALL(plant), [](pii a, pii b) {
        if (a.Y == b.Y) return a.X < b.X;
        return a.Y < b.Y;
    });
    
    int tok = 0;
    vector<int> dp(L + 1);
    for (int i = 1; i <= L; ++i) {
        dp[i] = dp[i - 1];
        while (plant[tok].Y == i) {
            dp[i] = max(dp[i], dp[plant[tok].X] + plant[tok].Y - plant[tok].X);
            ++tok;
        }
    }
    
    cout << dp[L] << "\n";
    
    return 0;
}
