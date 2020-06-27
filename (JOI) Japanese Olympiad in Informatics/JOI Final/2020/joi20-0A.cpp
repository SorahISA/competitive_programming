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
using prior = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = priority_queue<T>;

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

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 2E5 + 5;

int A[maxn], B[maxn], id[maxn], id2[maxn], pre[maxn], suf[maxn];

int32_t main() {
    fastIO();
    
    int n;
    cin >> n;
    
    for (int i = 0; i <= n; ++i) cin >> A[i], id[i] = i;
    for (int i = 0; i <  n; ++i) cin >> B[i];
    sort(id, id + n + 1, [](auto a, auto b) {return A[a] < A[b];});
    for (int i = 0; i <= n; ++i) id2[id[i]] = i;
    sort(A, A + n + 1), sort(B, B + n);
    
    for (int i = 1; i <= n; ++i) {
        pre[i] = max(pre[i-1], A[i-1] - B[i-1]);
    }
    for (int i = n-1; i >= 0; --i) {
        suf[i] = max(suf[i+1], A[i+1] - B[i]);
    }
    
    for (int i = 0; i <= n; ++i) {
        // cout << pre[id2[i]] << " " << suf[id2[i]] << "\n";
        cout << max(pre[id2[i]], suf[id2[i]]) << " \n"[i == n];
    }
    
    return 0;
}
