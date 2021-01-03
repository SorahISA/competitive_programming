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

const int mod = 1E9 + 7;

void solve() {
    int n; cin >> n;
    
    vector<int> val(n);
    for (auto &x : val) cin >> x;
    sort(ALL(val));
    
    vector<int> bits(60);
    for (auto x : val) {
        for (int i = 0; i < 60; ++i) {
            if (x >> i & 1) ++bits[i];
        }
    }
    
    // for (auto x : bits) cout << x << " "; cout << "\n";
    
    int ans = 0;
    for (auto x : val) {
        int sum_OR = 0;
        for (int i = 0; i < 60; ++i) {
            if (x >> i & 1) {
                sum_OR += (1LL << i) % mod * n % mod;
            }
            else {
                sum_OR += (1LL << i) % mod * bits[i] % mod;
            }
            sum_OR %= mod;
        }
        
        int sum_AND = 0;
        for (int i = 0; i < 60; ++i) {
            if (x >> i & 1) {
                sum_AND += (1LL << i) % mod * bits[i] % mod;
            }
            sum_AND %= mod;
        }
        
        ans += sum_OR % mod * sum_AND % mod;
    }
    cout << ans % mod << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}
