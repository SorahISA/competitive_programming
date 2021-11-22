#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

const int mod = 998244353;

void solve() {
    int P; cin >> P;
    
    /**
     * We want to calculate #{(x, y) : \exists n => x^n \equiv y in Z/PZ}
     * Since P is a prime, we have it primitive root, let it be r.
     * Now assume x = r^a and y = r^b, we get (r^{an} \equiv r^b),
     * which is equal to (an \equiv b) in Z/(P-1)Z.
     *
     * The sum we want to calaulate is \sum_{i=1}^{P-1}{\frac{P-1}{gcd(i, P-1)}} + 1
     * First get all divisors for P-1, then dp[i] = #{k : gcd(k, P-1) = divisor_i},
     * the number under 10^{12} with maximum number of divisors has 6720 divisors,
     * this algorithm works in O(P^{0.5} + (#divisor)^2), which is fast enough.
    **/
    
    vector<int> divisor;
    for (int i = 1; i*i <= P-1; ++i) {
        if ((P-1) % i == 0) {
            divisor.eb(i);
            if (i != (P-1) / i) divisor.eb((P-1) / i);
        }
    }
    sort(RALL(divisor));
    
    int sz = divisor.size(), ans = 1; /// (0, 0) is also an answer
    vector<int> dp(sz);
    for (int i = 0; i < sz; ++i) {
        dp[i] = (P-1) / divisor[i];
        for (int j = 0; j < i; ++j) {
            if (divisor[j] % divisor[i] == 0) dp[i] -= dp[j];
        }
        ans += ((P-1) / divisor[i] % mod) * (dp[i] % mod) % mod;
    }
    cout << ans % mod << "\n";
    
    // int test_ans = 1;
    // for (int i = 1; i <= P-1; ++i) {
        // test_ans = (test_ans + (P-1) / __gcd(i, P-1)) % mod;
    // }
    // cout << test_ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}