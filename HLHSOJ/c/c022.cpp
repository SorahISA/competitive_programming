#pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define int long long

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(0, MAXN); \
                 auto rnd = bind(__dis, __gen);

const int MAXN = 1E6;
const int mod = 1E9 + 7;
const int sqrtMax = 1 << 16;

namespace Gen {
    uint32_t S0, S1, S2, S3, mx;
    
    void Init() {
        cin >> S0 >> S1 >> S2 >> S3;
        if (S0 == 1) mx = 31;
        else if (S0 == 2) mx = (1 << 20) - 1;
        else mx = ((uint64_t)1 << 32) - 1;
    }
    
    inline uint32_t rot(const uint32_t x, int k) {
        return (x << k) | (x >> (32 - k));
    }
    
    uint32_t Rand() {
        uint32_t s0 = S0, s1 = S1, res = s0 + s1;
        s1 ^= s0;
        s0 = rot(s0, 24) ^ s1 ^ (s1 << 16);
        s1 = rot(s1, 17);
        S0 = s1, S1 = S2, S2 = S3, S3 = s0;
        return res & mx;
    }
}

struct Matrix {
    int a[2][2];
    
    void Init(int n1 = 0, int n2 = 0, int n3 = 0, int n4 = 0) {
        a[0][0] = n1, a[0][1] = n2;
        a[1][0] = n3, a[1][1] = n4;
    }
    
    Matrix operator * (const Matrix &rhs) const {
        Matrix tmp;
        tmp.a[0][0] = (a[0][0] * rhs.a[0][0] + a[0][1] * rhs.a[1][0]) % mod;
        tmp.a[0][1] = (a[0][0] * rhs.a[0][1] + a[0][1] * rhs.a[1][1]) % mod;
        tmp.a[1][0] = (a[1][0] * rhs.a[0][0] + a[1][1] * rhs.a[1][0]) % mod;
        tmp.a[1][1] = (a[1][0] * rhs.a[0][1] + a[1][1] * rhs.a[1][1]) % mod;
        
        return tmp;
    }
};

int32_t main() {
    fastIO();
    
    int T, x0, x1, a, b, ans = 0;
    cin >> T >> x0 >> x1 >> a >> b, Gen::Init();
    
    /// x_n = bx_{n-1} + ax_{n-2} ///
    /// x_0 = x0, x_1 = x1 ///
    
    vector<Matrix> small(sqrtMax), large(sqrtMax);
    
    small[0].Init(1, 0, 0, 1);
    small[1].Init(b, a, 1, 0);
    for (int i = 2; i < sqrtMax; ++i) {
        small[i] = small[i - 1] * small[1];
    }
    
    large[0].Init(1, 0, 0, 1);
    large[1] = small[sqrtMax - 1] * small[1];
    for (int i = 2; i < sqrtMax; ++i) {
        large[i] = large[i - 1] * large[1];
    }
    
    while (T--) {
        int ask = Gen::Rand();
        if (ask == 0) {ans ^= x0; continue;}
        else --ask;
        
        Matrix tmp = large[ask / sqrtMax] * small[ask % sqrtMax];
        // cerr << ask << ": " << (tmp.a[0][0] * x1 + tmp.a[0][1] * x0) % mod << "\n";
        ans ^= (tmp.a[0][0] * x1 + tmp.a[0][1] * x0) % mod;
    }
    
    cout << ans << "\n";
    
    return 0;
}
