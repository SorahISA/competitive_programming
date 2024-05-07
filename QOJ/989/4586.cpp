#ifndef Yamada
#define Yamada
#include Yamada __FILE__ Yamada

const int sigma = 26;
const int maxsz = 1000 * 1000 * 4 + 5;

void solve() {
    int R, C; cin >> R >> C;
    
    vector<string> grid(R);
    for (string &str : grid) cin >> str;
    
    int sum = 0;
    vector<int> cnt(sigma+1, 0);
    for (string &str : grid) for (char &c : str) {
        if (isalpha(c)) ++cnt[c - 'a' + 1], ++sum;
    }
    
    vector<bitset<maxsz>> dp(sigma+1);
    dp[0][0] = 1;
    for (int i = 1; i <= sigma; ++i) dp[i] = dp[i-1] | (dp[i-1] << cnt[i]);
    
    vector<int> maxV(maxsz, 0);
    for (int i = 1, lst = 0; i < maxsz; ++i) {
        if (dp[sigma][i]) lst = i;
        maxV[i] = lst;
    }
    
    int minRC = maxsz, R_opt = -1, C_opt = -1;
    for (int R_ = R; R_ <= 2*R; ++R_) for (int C_ = C; C_ <= 2*C; ++C_) {
        int evn = ((R_ + 1) / 2) * ((C_ + 1) / 2) + (R_ / 2) * (C_ / 2);
        int odd = R_ * C_ - evn;
        if (sum - maxV[evn] <= odd) {
            if (chmin(minRC, R_ * C_)) R_opt = R_, C_opt = C_;
        }
    }
    
    {
        // cerr << "? " << minRC << " " << R_opt << " " << C_opt << "\n";
        vector<string> ans(R_opt, string(C_opt, '.'));
        int evn = ((R_opt + 1) / 2) * ((C_opt + 1) / 2) + (R_opt / 2) * (C_opt / 2);
        // int odd = R_opt * C_opt - evn;
        vector<pii> pos_odd, pos_evn;
        for (int i = 0; i < R_opt; ++i) for (int j = 0; j < C_opt; ++j) {
            if ((i ^ j) & 1) pos_odd.eb(i, j);
            else             pos_evn.eb(i, j);
        }
        for (int c = sigma, now = maxV[evn]; c >= 1; --c) {
            if (dp[c-1][now]) {
                /// place in pos_odd ///
                // cerr << "? place " << char(c + 'a' - 1) << " in odd" << "\n";
                for (int i = 0; i < cnt[c]; ++i) {
                    ans[pos_odd.back().first][pos_odd.back().second] = char(c + 'a' - 1), pos_odd.pb();
                }
            }
            else {
                /// place in pos_evn ///
                // cerr << "? place " << char(c + 'a' - 1) << " in evn" << "\n";
                for (int i = 0; i < cnt[c]; ++i) {
                    ans[pos_evn.back().first][pos_evn.back().second] = char(c + 'a' - 1), pos_evn.pb();
                }
                now -= cnt[c];
            }
        }
        
        cout << R_opt << " " << C_opt << "\n";
        for (string &str : ans) cout << str << "\n";
    }
}

signed main() {
    IOS();
    int t = 1; // cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}

#else

#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using pii = pair<int,int>;

#define SZ(a) ((int)(a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front

#ifdef local
#define IOS() void()

#else
#define IOS() ios_base::sync_with_stdio(0); cin.tie(0);
#endif

template <typename U, typename V> bool chmin(U &u, V v) {return (u > v ? u = v, 1 : 0);}
template <typename U, typename V> bool chmax(U &u, V v) {return (u < v ? u = v, 1 : 0);}

#endif