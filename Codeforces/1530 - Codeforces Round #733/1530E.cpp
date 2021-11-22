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

void solve() {
    string s; cin >> s, sort(ALL(s));
    
    int N = s.size();
    vector<int> cnt(128, 0);
    for (auto &c : s) ++cnt[c];
    
    /// check if answer can be 0 ///
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        if (cnt[ch] != 1) continue;
        cout << ch;
        for (int i = 0; i < N; ++i) {
            if (s[i] != ch) cout << s[i];
        }
        return cout << "\n", void();
    }
    
    int kinds = 0;
    for (char ch = 'a'; ch <= 'z'; ++ch) kinds += cnt[ch] > 0;
    
    char small_0 = s[0], small_1 = '-', small_2 = '-';
    for (auto &c : s) {
        if (small_1 == '-' and c != s[0]) small_1 = c;
        if (small_2 == '-' and c != s[0] and c != small_1) small_2 = c;
    }
    
    if (kinds == 1 or cnt[small_0] == 1) return cout << s << "\n", void();
    
    string ans;
    
    if (cnt[small_0] <= N/2 + 1) {
        /// aaxaxaxaxaxa... ///
        ans += small_0, --cnt[small_0];
        ans += small_0, --cnt[small_0];
        for (char ch = small_0+1; ch <= 'z'; ++ch) {
            while (cnt[ch]) {
                ans += ch, --cnt[ch];
                if (cnt[small_0]) ans += small_0, --cnt[small_0];
            }
        }
    }
    else {
        if (kinds == 2) {
            /// abbb...bbaaaa... ///
            ans += small_0, --cnt[small_0];
            while (cnt[small_1]) ans += small_1, --cnt[small_1];
            while (cnt[small_0]) ans += small_0, --cnt[small_0];
        }
        else if (kinds > 2) {
            /// abaaa...aacbb...xx ///
            ans += small_0, --cnt[small_0];
            ans += small_1, --cnt[small_1];
            while (cnt[small_0]) ans += small_0, --cnt[small_0];
            ans += small_2, --cnt[small_2];
            for (char ch = small_1; ch <= 'z'; ++ch) {
                while (cnt[ch]) ans += ch, --cnt[ch];
            }
        }
    }
    
    assert(ans.size() == s.size());
    cout << ans << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}