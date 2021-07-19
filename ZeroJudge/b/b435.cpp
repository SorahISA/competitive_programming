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
#define pb pop_back
#define pf pop_front
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

int fastpow(int base, int exp, int mod, int ans = 1) {
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        base = base * base % mod, exp >>= 1;
    }
    return ans;
}

void solve(int P) {
    if (P == 2) return cout << 1 << "\n", void();
    if (P == 3) return cout << 2 << "\n", void();
    
    int phi_P = P - 1;
    vector<int> prime_factor;
    for (int i = 2, tmp_phi_P = phi_P; i*i <= tmp_phi_P; ++i) {
        if (tmp_phi_P % i == 0) {
            prime_factor.eb(i);
            while (tmp_phi_P % i == 0) tmp_phi_P /= i;
        }
        if ((i+1) * (i+1) > tmp_phi_P and tmp_phi_P != 1) prime_factor.eb(tmp_phi_P);
    }
    
    // cout << "prime factors: " << prime_factor << "\n";
    
    for (int m = 2; m < P; ++m) {
        int flag = 1;
        for (auto x : prime_factor) {
            if (fastpow(m, phi_P / x, P) == 1) flag = 0;
        }
        if (flag) return cout << m << "\n", void();
    }
}

int32_t main() {
    fastIO();
    
    int P;
    while (cin >> P) solve(P);
    
    return 0;
}