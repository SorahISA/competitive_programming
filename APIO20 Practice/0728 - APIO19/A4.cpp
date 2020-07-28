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
    if (A % 2 == 0) A /= 2;
    
    map<int, int> rng;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        if (r - l + 1 >= A) {++rng[0], --rng[A]; continue;}
        l %= A, r %= A;
        if (l <= r) ++rng[l], --rng[r + 1];
        else ++rng[l], --rng[A], ++rng[0], --rng[r + 1];
    }
    
    // cout << "-=-=-=-=-\n";
    // for (auto x : rng) cout << x.X << " " << x.Y << "\n";
    // cout << "-=-=-=-=-\n";
    
    int ans = 0, lst_num = 0, lst_sum = 0;
    for (auto x : rng) {
        x.Y += lst_sum;
        if (lst_sum > 0) ans += x.X - lst_num;
        lst_num = x.X;
        lst_sum = x.Y;
    }
    
    cout << ans << "\n";
    
    return 0;
}