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
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % (uint64_t)(R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

inline int __lcm(int x, int y) {return x / __gcd(x, y) * y;}

int fastpow(int base, int exp, int mod, int ans = 1) {
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return ans;
}

void solve() {
    int P, a, b; cin >> P >> a >> b;
    
    int cycA = 1, cycB = 1;
    for (int i = a; i != 1; i = i*a%P, ++cycA);
    for (int i = b; i != 1; i = i*b%P, ++cycB);
    
    if (cycA < cycB) swap(cycA, cycB), swap(a, b);
    
    if (cycA == P-1 or __lcm(cycA, cycB) == P-1) cout << "Yes\n";
    else return cout << "No\n", void();
    
    if (cycA == P-1) {
        int val = 1;
        do cout << val << " "; while ((val = val*a%P) != 1);
        cout << 1 << "\n";
    }
    else {
        cycB /= __gcd(cycA, cycB);
        if (cycA & 1) swap(cycA, cycB), swap(a, b);
        int invA = fastpow(a, P-2, P), invB = fastpow(b, P-2, P);
        
        /**
         *  +------+ b
         *  |>>>>>v|
         *  |^v<<<<|
         *  |^>>>>v|
         *  |^<<<<<|
         *  +------+
         *  a
        **/
        
        cout << 1 << " " << b << " ";
        int val = b;
        for (int i = 0; i < cycA; ++i) {
            if (i) val = val * a % P, cout << val << " ";
            for (int j = 1; j < cycB-1; ++j) val = val * (i & 1 ? invB : b) % P, cout << val << " ";
        }
        val = val * invB % P, cout << val << " ";
        for (int i = 0; i < cycA-1; ++i) val = val * invA % P, cout << val << " ";
        cout << "\n";
    }
    
    // cout << cycA << " " << cycB << "\n";
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