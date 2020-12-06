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

void solve() {
    int n, A, B;
    cin >> n >> A >> B;
    
    int cyc = log10(A) - log10(__gcd(A, B+1)) + log10(B) > 18.01 ? (int)1E18 + 100 : A / __gcd(A, B+1) * B;
    map<int, int> pre;
    
    while (n--) {
        int L, R;
        cin >> L >> R;
        if (R - L + 1 >= cyc) ++pre[0], --pre[cyc];
        else {
            L %= cyc, R %= cyc;
            if (L > R) ++pre[L], --pre[cyc], ++pre[0], --pre[R+1];
            else ++pre[L], --pre[R+1];
        }
    }
    
    int ans = 0, sum = 0, lst = 0;
    for (auto [key, val] : pre) {
        if (sum) ans += key - lst;
        sum += val, lst = key;
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    while (t--) solve();
    
    return 0;
}
