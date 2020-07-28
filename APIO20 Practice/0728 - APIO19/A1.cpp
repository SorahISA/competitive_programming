#include <bits/stdc++.h>
using namespace std;

#define int int64_t
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = priority_queue<T>;
template<typename T>
using prior = priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back
#define fastIO() ios_base::sync_with_stdio(false), cin.tie(0)

int32_t main() {
    fastIO();
    
    int n, A, B;
    cin >> n >> A >> B;
    
    set<pii> timer;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        while (l <= r) timer.insert({(l + l/B) % A, l % B}), ++l;
    }
    
    cout << timer.size() << "\n";
    
    return 0;
}