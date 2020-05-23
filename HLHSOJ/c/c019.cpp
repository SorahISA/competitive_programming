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
                 uniform_int_distribution<int> __dis(0, 1); \
                 auto rnd = bind(__dis, __gen);

const int INF = 1E18;
const int mod = 1E9 + 7;
const int BigInt_mod = 1E16;
const int BigInt_dig = 16;

struct BigInt {
    vector<int> v;
    
    BigInt(vector<int> _v = {0}) : v(_v) {}
    
    BigInt operator + (const BigInt rhs) const {
        BigInt tmp = v;
        int carry = 0;
        for (int i = 0; i < rhs.v.size(); ++i) {
            if (i >= tmp.v.size()) {
                tmp.v.eb(rhs.v[i] + carry);
                carry = tmp.v.back() / BigInt_mod;
                tmp.v.back() %= BigInt_mod;
            }
            else {
                tmp.v[i] += rhs.v[i] + carry;
                carry = tmp.v[i] / BigInt_mod;
                tmp.v[i] %= BigInt_mod;
            }
        }
        for (int i = rhs.v.size(); i < tmp.v.size(); ++i) {
            if (!carry) break;
            tmp.v[i] += carry;
            carry = tmp.v[i] / BigInt_mod;
            tmp.v[i] %= BigInt_mod;
        }
        if (carry) tmp.v.eb(1);
        return tmp;
    }
};

ostream& operator << (ostream &os, const BigInt rhs) {
    for (auto it = rhs.v.rbegin(); it != rhs.v.rend(); ++it) {
        if (it == rhs.v.rbegin()) os << *it;
        else cout << setw(BigInt_dig) << setfill('0') << *it;
    }
    return os;
}

BigInt ans[1005];

int32_t main() {
    fastIO();
    
    ans[0].v = ans[1].v = {1};
    for (int i = 2; i <= 1000; ++i) ans[i] = ans[i-1] + ans[i-2];
    
    int n;
    while (cin >> n) cout << ans[n] << "\n";
    
    return 0;
}
