// #pragma GCC optimize("Ofast", "unroll-loops")

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

const int maxc = 1E7;

vector<int> primes;
bitset<maxc> isprime;

void init() {
    isprime.set();
    isprime[0] = 0, isprime[1] = 0;
    for (int i = 2, j = i; i <= maxc; j = ++i) {
        if (isprime[i]) {
            while ((j += i) <= maxc) isprime[j] = 0;
            primes.eb(i);
        }
    }
}

void solve() {
    auto cnt_fac = [](int x, int p, int ans = 0) {
        while (x >= p) ans += x /= p;
        return ans;
    };
    
    int a, b, c, d; cin >> a >> b >> c >> d;
    for (auto p : primes) {
        if (cnt_fac(b, p) - cnt_fac(a-1, p) > cnt_fac(d, p) - cnt_fac(c-1, p)) {
            cout << "NE\n"; return;
        }
    }
    cout << "DA\n";
}

int32_t main() {
    fastIO();
    init();
    
    int t = 1; cin >> t;
    while (t--) solve();
    
    return 0;
}
