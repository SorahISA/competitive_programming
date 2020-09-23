#include <bits/stdc++.h>
using namespace std;

int main() {
    int a[3], b[3];
    cin >> a[0] >> a[1] >> a[2]; sort(a, a + 3);
    cin >> b[0] >> b[1] >> b[2]; sort(b, b + 3);
    if (a[0] * a[0] + a[1] * a[1] != a[2] * a[2]) cout << "NO\n";
    else if (a[0] == b[0] and a[1] == b[1] and a[2] == b[2]) cout << "YES\n";
    else cout << "NO\n";
}