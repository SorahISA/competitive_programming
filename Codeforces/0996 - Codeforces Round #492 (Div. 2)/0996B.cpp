#include <bits/stdc++.h>
using namespace std;

using lli = long long;
using Double = long double;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;
    
    int v[n], Min = 1E9;
    for (int i = 0; i < n; ++i) cin >> v[i], Min = min(Min, v[i] -= i);
    
    int Round = Min / n + (Min % n > 0);
    assert(Round >= 0);
    
    for (int i = 0; i < n; ++i) {
        if (v[i] - Round * n <= 0) {
            cout << i + 1 << "\n";
            break;
        }
    }
    
    return 0;
}
