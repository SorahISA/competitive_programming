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

const int INF = 1E18;
const int mod = 1E9 + 7;
const int maxn = 2E5 + 5;

int32_t main() {
    fastIO();
    
    int n;
    cin >> n;
    
    vector<int> ans_xor(n);
    int ans_and_01, ans_and_02;
    for (int i = 1; i < n; ++i) {
        cout << "XOR " << 0+1 << " " << i+1 << endl;
        cin >> ans_xor[i];
    }
    
    int is_permutation = 1;
    vector<int> tmp_ans_xor = ans_xor;
    sort(ALL(tmp_ans_xor));
    for (int i = 0; i < n; ++i) is_permutation &= tmp_ans_xor[i] == i;
    
    if (is_permutation) {
    
        int n_0 = 0, n_1 = 0, n_2 = 0;
        for (int i = 0; i < n; ++i) {
            if (ans_xor[i] == 0) n_0 = i;
            if (ans_xor[i] == 1) n_1 = i;
            if (ans_xor[i] == 2) n_2 = i;
        }
        
        cout << "AND " << n_0+1 << " " << n_1+1 << endl;
        cin >> ans_and_01; /// +1
        
        cout << "AND " << n_0+1 << " " << n_2+1 << endl;
        cin >> ans_and_02; /// +2
        
        int num_0 = 0;
        if (ans_and_01     == ans_and_02 or ans_and_01     == ans_and_02 + 2) num_0 = ans_and_01;
        if (ans_and_01 + 1 == ans_and_02 or ans_and_01 + 1 == ans_and_02 + 2) num_0 = ans_and_01 + 1;
        
        cout << "! ";
        for (auto x : ans_xor) cout << (x ^ num_0) << " ";
        cout << endl;
        
    }
    else {
        
        int repeat_num = 0;
        for (int i = 1; i < n; ++i) {
            if (tmp_ans_xor[i-1] == tmp_ans_xor[i]) repeat_num = tmp_ans_xor[i];
        }
        
        int ind1 = -1, ind2 = -1;
        for (int i = 0; i < n; ++i) {
            if (ans_xor[i] == repeat_num) {
                if (ind1 == -1) ind1 = i;
                else            ind2 = i;
            }
        }
        
        int real_repeat_num, xor_value;
        cout << "OR " << ind1+1 << " " << ind2+1 << endl;
        cin >> real_repeat_num, xor_value = repeat_num ^ real_repeat_num;
        
        cout << "! ";
        for (auto x : ans_xor) cout << (x ^ xor_value) << " ";
        cout << endl;
    }
    
    return 0;
}
