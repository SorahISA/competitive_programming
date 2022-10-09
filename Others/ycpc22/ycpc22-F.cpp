#include <bits/stdc++.h>
#define int long long
#define double long double
using namespace std;
using pii = pair<int, int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;
#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define eb emplace_back
#define X first
#define Y second
#ifdef local
#define debug(...) do{\
    fprintf(stderr, "LINE %d: (%s) = ", __LINE__, #__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template <typename T> void _do(T &&_x) {cerr << _x << endl;}
template <typename T, typename ...S> void _do(T &&_x, S &&..._t){cerr << _x << ", "; _do(_t...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

template <typename T, typename U> bool chmin(T &lhs, U rhs){return lhs > rhs ? lhs = rhs, 1 : 0;}
template <typename T, typename U> bool chmax(T &lhs, U rhs){return lhs < rhs ? lhs = rhs, 1 : 0;}

const int maxn = 2e5 + 5;

__int128 sum[maxn], mul[maxn], arr[maxn];
__int128 n, k;

__int128 cal(__int128 l, __int128 r) {
    return mul[r] - mul[l - 1] - (sum[r] - sum[l - 1]) * (l - 1);
}

void solve() {
    int _n, _k;
    cin >> _n >> _k, n = _n, k = _k;
    for(__int128 i = 1; i <= n; i++) {
        int tmp;
        cin >> tmp, arr[i] = tmp;
        sum[i] = sum[i - 1] + arr[i];
        mul[i] = mul[i - 1] + arr[i] * i;  
    }
    __int128 ans = 0;
    for(__int128 i = 1; i <= n; i++) {
        if(arr[i] > k) continue;
        __int128 l = i, r = n + 1;
        while(r - l > 1) {
            __int128 mid = (l + r) >> 1;
            if(cal(i, mid) <= k)
                l = mid;
            else    
                r = mid;
        }
        ans += (r - i);
    }
    cout << (int64_t)ans << '\n';
}

signed main() {
    IOS();
    int _ = 1;
    // cin >> _;
    for (int i=1;i<=_;++i) {
        solve();
    }
}
