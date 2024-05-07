#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double

#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)

int32_t main() {
    string S; cin >> S;
    for (int i = 0; i < SZ(S); i += 4) {
        if (S[i+1] == 'o') return cout << i / 4 + 1 << "\n", 0;
    }
    cout << "none\n";
}
