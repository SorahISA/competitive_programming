#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;

signed main() {
    double a,b,c,d;
    cin >> a >> b >> c >> d;
    double s = (a + b + c + d) / 2;
    cout << fixed << setprecision(15) << sqrt((s - a) * (s - b) * (s - c) * (s - d)) << endl;
}
