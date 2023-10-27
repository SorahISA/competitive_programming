#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

void solve() {
    int t1, v1; cin >> t1 >> v1;
    int t2, v2; cin >> t2 >> v2;
    
         if (t2 < 0 and v2 >= 10) cout << "A storm warning for tomorrow! Be careful and stay home if possible!" << "\n";
    else if (t2 < t1)             cout << "MCHS warns! Low temperature is expected tomorrow." << "\n";
    else if (v2 > v1)             cout << "MCHS warns! Strong wind is expected tomorrow." << "\n";
    else                          cout << "No message" << "\n";
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}

#else

#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using pii = pair<int,int>;

#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)


#ifdef local
#define IOS() void()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#endif

#endif