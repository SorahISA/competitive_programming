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

int32_t main() {
    fastIO();
    
    string S, A, C;
    getline(cin, S), getline(cin, A);
    S = '\n' + S;
    
    int lenS = S.size(), lenA = A.size(), lenC = lenA / 10 * 32;
    for (int i = 0; i < lenA; i += 10) {
        C += bitset<32>(stoll(A.substr(i, 10))).to_string();
    }
    
    string ans;
    int pot = __lg(lenS); /// pow_of_two ///
    for (int i = lenC; i > 0; i -= pot) {
        ans += S[bitset<8>(C.substr(max(0LL, i-pot), min(i, pot))).to_ullong()];
    }
    reverse(ALL(ans));
    
    int fl = 0;
    for (auto c : ans) cout << (fl or c != '\n' ? fl = 1, string{c} : "");
    
    return 0;
}
