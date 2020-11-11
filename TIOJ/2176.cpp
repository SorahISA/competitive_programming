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

vector<int> a, b, c;

int calc(int N, int x) {
    int sum_a = 0, sum_b = 0, sum_c = 0;
    for (int i =   x; i <= N; i += x) sum_a += a[i], sum_b += b[i];
    for (int i = 2*x; i <= N; i += x) sum_c += c[i];
    return sum_a * sum_b - sum_c;
}

int32_t main() {
    fastIO();
    
    int n;
    cin >> n, a.resize(n+1), b.resize(n+1), c.resize(n+1);
    
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    
    for (int i = n; i >= 1; --i) c[i] = calc(n, i);
    
    for (int i = 1; i <= n; ++i) cout << c[i] << " \n"[i == n];
    
    return 0;
}

/*

c_i = \sum_{1 \le j, k \le N, \gcd(j, k) = i}{a_j \times b_k}
    = \sum_{j = 1}^{\lfloor\frac{N}{i}\rfloor}{a_{i \times j}} \times \sum_{k = 1}^{\lfloor\frac{N}{i}\rfloor}{b_{i \times k}}
      - \sum_{1 \le j, k \le N, \gcd(j, k) = mi, m > 1}{a_j \times b_k}
    = \sum_{j = 1}^{\lfloor\frac{N}{i}\rfloor}{a_{i \times j}} \times \sum_{j = 1}^{\lfloor\frac{N}{i}\rfloor}{b_{i \times j}}
      - \sum_{j = 2}^{\lfloor\frac{N}{i}\rfloor}{c_{i \times j}}

\sum_{i = 1}^{N}{\frac{1}{i}} = O(N \lg N)

*/
