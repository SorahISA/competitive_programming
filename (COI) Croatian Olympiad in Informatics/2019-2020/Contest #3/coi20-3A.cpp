#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

int32_t main() {
    fastIO();
    
    int n, tmp, tok = 0, lst = 1, lstState = 0, nowState = 0;
    int A = 0, B = 0, Tie = 1, Turn = 0;
    cin >> n;
    
    vector<int> v(1, 0);
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        if (tmp == lst) ++*prev(v.end());
        else v.push_back(1);
        lst = tmp;
            
        if (tmp == 1) ++A;
        else          ++B;
        if (A == B) ++Tie;
    }
    
    cout << A << " " << B << "\n";
    cout << Tie << "\n";
    
    A = B = 0;
    for (auto x : v) {
        if (~(tok++) & 1) A += x;
        else              B += x;
        lstState = nowState;
        nowState = (A == B ? 0 : (A > B ? 1 : 2));
        if (lstState and nowState and lstState != nowState) Turn = max(Turn, x);
    }
    
    cout << Turn << "\n";
    
    return 0;
}
