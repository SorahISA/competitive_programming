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
const int maxn = 1E5 + 5;

int n, m, goal, ans;
int arr[maxn];

void search(int L, int R, int aL, int aR, int now) {
    // cout << L << " " << R << "\n";
    if (L + 1 == R) {ans = L; return;}
    int M = L + R >> 1;
    int all = M - L;
    int cnt = lower_bound(arr + aL, arr + aR, M) - (arr + aL);
    if (now + all - cnt >= goal) search(L, M, aL, aL+cnt, now);
    else                         search(M, R, aL+cnt, aR, now+all-cnt);
}

void solve() {
    cin >> n >> m, goal = ((1LL<<m)-n-1) / 2 + 1;
    for (int i = 0; i < n; ++i) {
        int val = 0;
        string s; cin >> s;
        for (auto c : s) val = 2*val + (c == '1');
        arr[i] = val;
    }
    sort(arr, arr + n);
    
    search(0, 1LL<<m, 0, n, 0);
    
    string ANS;
    for (int i = 0; i < m; ++i) ANS += (ans&1 ? '1' : '0'), ans >>= 1;
    reverse(ALL(ANS));
    
    cout << ANS << "\n";
}

int32_t main() {
    fastIO();
    
    int t;
    cin >> t;
    while (t--) solve();
    
    return 0;
}
