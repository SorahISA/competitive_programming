#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pf pop_front
#define pb pop_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % ((uint64_t)R - L + 1) + L);
}

template<typename T1, typename T2>
ostream& operator << (ostream &os, pair<T1, T2> &p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

template<typename T>
ostream& operator << (ostream &os, vector<T> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (i) os << " ";
        os << vec[i];
    }
    return os;
}

void chmin(int &x, int y) {x = min(x, y);}

void solve() {
    string S; cin >> S;
    int N = S.size();
    
    vector<int> cnt(26, 0);
    for (auto &c : S) ++cnt[c-'A'];
    
    int cnt_vowel = cnt['A'-'A'] + cnt['E'-'A'] + cnt['I'-'A'] + cnt['O'-'A'] + cnt['U'-'A'];
    int cnt_conso = N - cnt_vowel;
    
    int ans = N * 2;
    for (auto c : "AEIOU") {
        if (!isupper(c)) break;
        chmin(ans, (cnt_vowel - cnt[c-'A']) * 2 + cnt_conso * 1);
    }
    for (auto c : "BCDFGHJKLMNPQRSTVWXYZ") {
        if (!isupper(c)) break;
        chmin(ans, (cnt_conso - cnt[c-'A']) * 2 + cnt_vowel * 1);
    }
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}