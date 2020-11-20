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

const int maxn = 1E5 + 5;

int32_t main() {
    fastIO();
    
    int n, k;
    cin >> n >> k;
    
    vector<int> v(n+1);
    for (int i = 1; i <= n; ++i) cin >> v[i], --v[i];
    partial_sum(ALL(v), v.begin());
    
    int ans = 0;
    map<int, int> prefix;
    for (int i = 0; i <= n; ++i) {
        if (i >= k) --prefix[v[i-k] % k];
        ans += prefix[v[i] % k]++;
    }
    
    cout << ans << "\n";
    
    return 0;
}
