#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;
#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

const int INF = 1E18;

int32_t main() {
    fastIO();
    
    int a, b;
    cin >> a >> b;
    if (a < b) swap(a, b);
    while (b) a %= b, swap(a, b);
    cout << a << "\n";
    
    return 0;
}
