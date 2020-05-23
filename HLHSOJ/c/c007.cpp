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
const double eps = 1e-6;

int32_t main() {
    // fastIO();
    
    int a, b, res;
    char c;
    scanf("%lld%c%lld", &a, &c, &b);
    
    int digA, digB, digRes, len;
    digA = floor(log10(a + eps)) + 1;
    digB = floor(log10(b + eps)) + 1 + 1;
    
    if (c == '+') {
        res = a + b;
        digRes = floor(log10(res + eps)) + 1;
        len = max({digA, digB, digRes});
        string sa(len-digA, '#'), sb(len-digB, '#'), sres(len-digRes, '#');
        string lineL(len-max(digA, digB), '#'), lineR(max(digA, digB), '-');
        cout << sa << a << "\n";
        cout << sb << "+" << b << "\n";
        cout << lineL << lineR << "\n";
        cout << sres << res << "\n";
    }
    if (c == '-') {
        res = a - b;
        digRes = floor(log10(res + eps)) + 1;
        len = max({digA, digB, digRes});
        string sa(len-digA, '#'), sb(len-digB, '#'), sres(len-digRes, '#');
        string lineL(len-max(digA, digB), '#'), lineR(max(digA, digB), '-');
        cout << sa << a << "\n";
        cout << sb << "-" << b << "\n";
        cout << lineL << lineR << "\n";
        cout << sres << res << "\n";
    }
    if (c == '*') {
        res = a * b;
        digRes = floor(log10(res + eps)) + 1;
        len = max({digA, digB, digRes});
        string sa(len-digA, '#'), sb(len-digB, '#'), sres(len-digRes, '#');
        string lineL(len-max(digA, digB), '#'), lineR(max(digA, digB), '-'), line(len, '-');
        cout << sa << a << "\n";
        cout << sb << "*" << b << "\n";
        cout << lineL << lineR << "\n";
        
        for (int i = 0; b > 0; ++i, b /= 10) {
            int tmp = a * (b % 10);
            int digTmp = tmp == 0 ? 1 : floor(log10(tmp + eps)) + 1;
            string stmpL(len-i-digTmp, '#'), stmpR(i, '#');
            cout << stmpL << tmp << stmpR << "\n";
        }
        
        cout << line << "\n";
        cout << sres << res << "\n";
    }
    
    return 0;
}
