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
    
    int n, k;
    string s;
    cin >> n >> k >> s;
    
    int maxLen = 1, minSt = 0, maxHi = 1, maxLo = 1;
    for (int i = 0; i < n; ++i) {
        int rep = 0;
        set<char> valC, valD;
        valC.insert(s[i]);
        valD.insert(isdigit(s[i]) ? '0' : (isupper(s[i]) ? 'A' : (islower(s[i]) ? 'a' : '#')));
        for (int j = i+1; j < n; ++j) {
            if (j-i+1 > k) break;
            valC.insert(s[j]);
            valD.insert(isdigit(s[j]) ? '0' : (isupper(s[j]) ? 'A' : (islower(s[j]) ? 'a' : '#')));
            rep += s[j] == s[j-1];
            int Hi = valC.size() * valD.size(), Lo = rep + 1, gcd = __gcd(Hi, Lo);
            Hi /= gcd, Lo /= gcd;
            
            if (Hi * maxLo == Lo * maxHi and j-i+1 > maxLen) maxLen = j-i+1, minSt = i;
            else if (Hi * maxLo > Lo * maxHi) maxLen = j-i+1, minSt = i, maxHi = Hi, maxLo = Lo;
        }
    }
    
    cout << s.substr(minSt, maxLen) << "\n";
    
    return 0;
}
