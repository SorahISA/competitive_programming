// #pragma GCC target("avx2")
#pragma GCC optimize("O3", "unroll-loops")

// #include <bits/extc++.h>
// using namespace __gnu_pbds;

#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
// template <typename T>
// using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
using pii = pair<int, int>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

#define X first
#define Y second
#define ALL(x) (x).begin(), (x).end()
#define eb emplace_back
#define pb push_back

#define fastIO() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define RANDOM() random_device __rd; \
                 mt19937 __gen = mt19937(__rd()); \
                 uniform_int_distribution<int> __dis(1, 1E8); \
                 auto rnd = bind(__dis, __gen)

const int INF = 1E9;
const int mod = 998244353;

vector<int> arr;

int fpow(int base, int exp, int ans = 1) {
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return ans;
}

int calc(int N, int k) {
    return (fpow(2, k) - 1) * fpow(2, N-k) % mod;
}

int recur(int N) {
    for (int i = N-1, cnt = 0; i >= 0; --i) {
        if (arr[i] == arr[N-1]) ++cnt;
        else return (arr[N-1] * calc(N, cnt) + recur(i+1)) % mod;
    }
    return arr[N-1] * calc(N, N) % mod;
}

int32_t main() {
    fastIO();
    
    int n;
    cin >> n, arr.resize(n);
    
    for (auto &x : arr) cin >> x;
    sort(ALL(arr));
    
    cout << recur(n) << "\n";
    
    return 0;
}
