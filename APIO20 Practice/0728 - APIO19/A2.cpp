#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

int32_t main() {
    fastIO();
    
    int n, A, B, d, l, r;
    cin >> n >> A >> B;
    d = __gcd(A, B + 1);
    
    cin >> l >> r;
    if ((int)(((double)d * (r - l + 1)) / (double)A) <= B) cout << r - l + 1 << "\n";
    else {
        int cnt = (r - l + 1) / B;
        cout << min(cnt, A / d) * B << "\n";
    }
    
    return 0;
}