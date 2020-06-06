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

int32_t main() {
    fastIO();
    
    int sz;
    string s;
    cin >> s, sz = s.size();
    
    vector<int> pow_of_three(1, 1);
    for (int i = 1; i < sz; ++i) pow_of_three.eb(pow_of_three.back() * 3 % mod);
    
    vector<int> pre(sz, 0), suf(sz, 0), q_pre(sz, 0), q_suf(sz, 0);
    for (int i = 0; i < sz; ++i) {
          pre[i] = (i ?   pre[i-1] : 0LL) + (s[i] == 'A');
        q_pre[i] = (i ? q_pre[i-1] : 0LL) + (s[i] == '?');
    }
    for (int i = sz-1; i >= 0; --i) {
          suf[i] = (i != sz-1 ?   suf[i+1] : 0LL) + (s[i] == 'C');
        q_suf[i] = (i != sz-1 ? q_suf[i+1] : 0LL) + (s[i] == '?');
    }
    
    int ans = 0;
    for (int i = 1; i < sz-1; ++i) {
        if (s[i] == 'B' or s[i] == '?') {
            int a = pre[i-1], c = suf[i+1], ql = q_pre[i-1], qr = q_suf[i+1], pl, pr;
            // cerr << a << " " << c << " " << ql << " " << qr << "\n";
            if (ql) pl = (a * 3 + ql) * pow_of_three[ql - 1] % mod;
            else pl = a;
            if (qr) pr = (c * 3 + qr) * pow_of_three[qr - 1] % mod;
            else pr = c;
            ans = (ans + pl * pr) % mod;
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
