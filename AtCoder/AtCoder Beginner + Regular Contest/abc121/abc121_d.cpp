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
    
    int A, B;
    cin >> A >> B;
    
    int ans = 0;
    for (; A % 4; ++A) ans ^= A;
    for (; B % 4; --B) ans ^= B;
    ans ^= B;
    
    cout << ans << "\n";
    
    return 0;
}
