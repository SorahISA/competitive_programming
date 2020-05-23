#include <bits/stdc++.h>
using namespace std;

#define int unsigned long long

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

const int mod = 1E9 + 7;
const int maxn = 36E5 + 5;

int pow_of_two[maxn], prefixSum[maxn];

void precal() {
    pow_of_two[0] = 1;
    for (int i = 1; i < maxn; ++i) pow_of_two[i] = pow_of_two[i - 1] * 2 % mod;
    
    prefixSum[0] = 0;
    for (int i = 1; i < maxn; ++i) prefixSum[i] = prefixSum[i - 1] + i*i;
}

inline int Sum(int L, int R) {
    return prefixSum[R] - prefixSum[L - 1];
    // return (R * (R+1) * (2*R+1) / 6) - ((L-1) * L * (2*L-1) / 6);
}

void solve() {
    int64_t _n, _k;
    cin >> _n >> _k;
    
    int n = _n, k = _k, lo, hi, mi, nxtMin = 1, nowLen, ans = 0;
    
    if (Sum(n, n) > k) {
        cout << -1 << "\n";
        return;
    }
    
    if (Sum(1, n) <= k) {
        cout << 1 << "\n";
        return;
    }
    
    while (nxtMin <= n) {
        lo = nxtMin, hi = n + 1;
        while (lo < hi) {
            mi = (lo + hi) >> 1;
            if (Sum(nxtMin, mi) > k) hi = mi;
            else lo = mi + 1;
        }
        
        nowLen = lo - nxtMin;
        // cerr << "len: " << nowLen << ", ";
        
        if (Sum(lo, lo + nowLen - 1) <= k) {
            lo = nxtMin, hi = n - nowLen + 2;
            while (lo < hi) {
                mi = (lo + hi) >> 1;
                if (Sum(mi, mi + nowLen - 1) > k) hi = mi;
                else lo = mi + 1;
            }
            
            ans += ((lo+nowLen-1) - nxtMin) / nowLen;
            nxtMin += ((lo+nowLen-1) - nxtMin) / nowLen * nowLen;
        }
        else {
            ans += 1;
            nxtMin = lo;
        }
        
        // cerr << "nxt: " << nxtMin << "\n";
    }
    
    // cerr << ans << "\n";
    cout << pow_of_two[ans] - 1 << "\n";
}

int32_t main() {
    fastIO();
    precal();
    
    int32_t t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
