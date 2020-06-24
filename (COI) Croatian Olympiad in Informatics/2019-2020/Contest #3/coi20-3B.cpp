#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

const int maxn = 1 << 17;

int BIT[26][maxn];

int lb(int x) {
    return x & -x;
}

void ADD(int al, int pl, int val = 1) {
    for (; pl < maxn; pl += lb(pl)) {
        BIT[al][pl] += val;
    }
}

int SUM(int al, int pl, int pr) {
    --pl;
    int ans = 0;
    for (; pr; pr -= lb(pr)) ans += BIT[al][pr];
    for (; pl; pl -= lb(pl)) ans -= BIT[al][pl];
    return ans;
}

int32_t main() {
    fastIO();
    
    int n, q, tok = 0, tmp, fl;
    string s;
    cin >> s >> q, n = s.size();
    s = " " + s;
    
    vector<pair<int, int>> v(q);
    for (auto &[L, R] : v) cin >> L >> R;
    
    /// Build 26 BITs for 'a'-'z' ///
    for (int i = 1; i <= n; ++i) {
        ADD(s[i] - 'a', i);
    }
    
    /// Query for every deletion ///
    for (int i = 0; i <= n; ++i) {
        if (i) {
            cin >> tmp;
            ADD(s[tmp] - 'a', tmp, -1);
        }
        
        for (; tok < q; ++tok) {
            fl = 1;
            for (int p = 0; p < 26 and fl; ++p) {
                if (SUM(p, v[tok].first, v[tok].second) > 1) fl = 0;
            }
            if (!fl) break;
        }
        
        if (tok == q) {
            cout << i << "\n";
            return 0;
        }
    }
    
    return 0;
}
