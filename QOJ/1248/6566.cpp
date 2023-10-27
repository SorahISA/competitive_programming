#include <bits/stdc++.h>
using namespace std;

#define int int64_t

const int sq3C = 1'000'000;

bool chk_prime(int x) {
    for (int i = 2; i*i <= x; ++i) {
        if (x % i == 0) return false;
    }
    return true;
}

void solve() {
    int X; cin >> X;
    
    if (X > sq3C) {
        int sqX = sqrtl(X);
        for (int i = sqX-3; i <= sqX+3; ++i) {
            if (i * i == X and chk_prime(i)) return cout << i << "\n", void();
        }
    }
    
    bitset<sq3C> is_prime; is_prime.set();
    vector<int> div_cnt(sq3C+1), max_pf(sq3C+1);
    div_cnt[1] = 1;
    for (int i = 2; i <= sq3C; ++i) {
        if (is_prime[i]) {
            max_pf[i] = i, div_cnt[i] = 2;
            for (int j = i+i; j <= sq3C; j += i) is_prime[j] = 0, max_pf[j] = i;
        }
        else {
            int j = i, cnt = 1;
            while (j % max_pf[i] == 0) j /= max_pf[i], ++cnt;
            div_cnt[i] = div_cnt[j] * cnt;
        }
    }
    
    for (int i = 1; i <= sq3C; ++i) {
        __int128_t val = 1;
        for (int exp = 1; exp <= div_cnt[i]; ++exp) {
            val *= i;
            if (val > X) break;
        }
        if (val == X) return cout << i << "\n", void();
    }
    
    cout << -1 << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    
    solve();
    
    return 0;
}
