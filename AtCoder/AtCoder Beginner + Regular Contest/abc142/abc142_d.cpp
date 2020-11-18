#pragma GCC optimize("Ofast", "unroll-loops")

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
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

const int maxn = 1E5 + 5;

int32_t main() {
    fastIO();
    
    int A, B, C;
    cin >> A >> B, C = __gcd(A, B);
    
    map<int, int> div{{1, 1}};
    for (int i = 2; i*i <= C; ++i) {
        while (C % i == 0) ++div[i], C /= i;
    }
    ++div[C];
    
    cout << div.size() << "\n";
    
    return 0;
}
