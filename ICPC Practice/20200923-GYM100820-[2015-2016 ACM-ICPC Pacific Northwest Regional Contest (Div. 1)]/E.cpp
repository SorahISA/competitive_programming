#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double

#define ALL(x) (x).begin(), (x).end()
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

const int INF = 1E18;

int32_t main() {
    fastIO();
    
    int n, minAns = INF;
    cin >> n;
    
    vector<int> v(n);
    for (auto &x : v) cin >> x;
    sort(ALL(v));
    
    for (int i = 0; i < n/2; ++i) {
        minAns = min(minAns, v[i] + v[n-i-1]);
    }
    
    cout << minAns << "\n";
    
    return 0;
}