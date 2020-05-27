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

const int INF = 3E18;
const int mod = 1E9 + 7;
const int maxn = 1E5 + 5;

string ans;
vector<int> len(maxn);
string f0 = "What are you doing at the end of the world? Are you busy? Will you save us?";
string f1 = "What are you doing while sending \"" + f0 + "\"? Are you busy? Will you send \"" + f0 + "\"?";
string strL = "What are you doing while sending \"";
string strM = "\"? Are you busy? Will you send \"";
string strR = "\"?";
int lenL = strL.size(), lenM = strM.size(), lenR = strR.size();

void recur(int lay, int left) {
    // cout << "(lay, left) : " << lay << ", " << left << "\n";
    if (lay == 0 and left <= len[0]) {ans.pb(f0[left - 1]); return;}
    else if (lay == 0) {ans.pb('.'); return;}

         if (left <= lenL) {
        /// a char in part A ///
        ans.pb(strL[left - 1]);
    }
    else if (left <= lenL + len[lay-1]) {
        recur(lay - 1, left - lenL);
    }
    else if (left <= lenL + lenM + len[lay-1]) {
        /// a char in part B //
        left -= lenL + len[lay-1];
        ans.pb(strM[left - 1]);
    }
    else if (left <= lenL + lenM + len[lay-1]*2) {
        recur(lay - 1, left - lenL - lenM - len[lay-1]);
    }
    else if (left <= lenL + lenM + lenR + len[lay-1]*2) {
        /// a char in part C ///
        left -= lenL + lenM + len[lay-1]*2;
        ans.pb(strR[left - 1]);
    }
    else {
        /// no answer ///
        ans.pb('.');
    }
}

int32_t main() {
    fastIO();
    
    
    len[0] = f0.size();
    len[1] = f1.size();

    for (int i = 2; i < maxn; ++i) {
        len[i] = min(INF, 2*len[i-1] + (lenL+lenM+lenR));
        // f1 = "What are you doing while sending \"" + f1 + "\"? Are you busy? Will you send \"" + f1 + "\"?";
        // cout << setw(8) << len[i] << " : " << f1 << "\n";
    }

    // cout << lenL << " " << lenM << " " << lenR << "\n";

    int q, n, k;
    cin >> q;
    while (q--) cin >> n >> k, recur(n, k);
    
    cout << ans << "\n";

    return 0;
}
