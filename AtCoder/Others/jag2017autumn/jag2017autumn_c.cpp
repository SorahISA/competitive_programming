#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T> using Prior = std::priority_queue<T>;
template<typename T> using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &x, T y) {return x > y ? x = y, 1 : 0;}
template<typename T> bool chmax(T &x, T y) {return x < y ? x = y, 1 : 0;}

const int maxlen = 1E6;

bitset<maxlen> isprime;

vector<int> primes;

void prime_sieve() {
    isprime.set(), isprime[0] = isprime[1] = 0;
    for (int i = 2; i < maxlen; ++i) {
        if (isprime[i]) {
            primes.eb(i);
            for (int j = i*i; j < maxlen; j += i) isprime[j] = 0;
        }
    }
}

void solve() {
    // for (auto p : primes) cout << p << "\n";
    
    int L, R; cin >> L >> R;
    
    int len = R - L + 1;
    vector<int> arr, cnt(len, 0);
    for (int i = L; i <= R; ++i) arr.eb(i);
    
    for (auto p : primes) {
        int st = (p - L % p) % p;
        for (int i = st; i < len; i += p) {
            while (arr[i] % p == 0) arr[i] /= p, ++cnt[i];
        }
        // for (auto x : arr) cout << x << " ";
        // cout << "\n";
    }
    
    for (int i = 0; i < len; ++i) {
        if (arr[i] > 1) ++cnt[i];
    }
    
    int ans = 0;
    for (auto x : cnt) ans += isprime[x];
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    prime_sieve();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        solve();
    }
    
    return 0;
}