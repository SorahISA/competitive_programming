#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// #define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define pb pop_back
#define pf pop_front
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

const int INF = INT_MAX;
const int maxn = 30 * (int)2E5 + 10;

template<size_t sz>
struct Trie {
    int sub[sz][2];
    
    Trie() {
        memset(sub, 0xff, sizeof(sub));
    }
    
    void Insert(int x) {
        static int tok = 0;
        int now = 0;
        for (int i = 29; i >= 0; --i) {
            if (sub[now][x>>i&1] == -1) sub[now][x>>i&1] = ++tok;
            now = sub[now][x>>i&1];
        }
    }
    
    int FindMinXor(int L, int R) {
        int ans = INF;
        deque<int> deqL{L}, deqR{R}, val{1};
        while (!deqL.empty()) {
            int nowL = deqL.back(), nowR = deqR.back(), nowV = val.back(), fl = 0;
            deqL.pb(), deqR.pb(), val.pb();
            for (int i : {0, 1}) {
                if (sub[nowL][i] != -1) {
                    fl = 1;
                    deqL.eb(sub[nowL][i]);
                    if (sub[nowR][i] != -1) deqR.eb(sub[nowR][i]),   val.eb(nowV << 1);
                    else                    deqR.eb(sub[nowR][i^1]), val.eb(nowV << 1 | 1);
                }
            }
            if (!fl) ans = min(ans, nowV);
        }
        return ans;
    }
    
    int64_t recur(int idx, int dep) {
        if (dep < 0) return 0;
        if (sub[idx][0] != -1 and sub[idx][1] != -1) {
            return FindMinXor(sub[idx][0], sub[idx][1])
                + recur(sub[idx][0], dep - 1) + recur(sub[idx][1], dep - 1);
        }
        else if (sub[idx][0] != -1) return recur(sub[idx][0], dep - 1);
        else if (sub[idx][1] != -1) return recur(sub[idx][1], dep - 1);
    }
};

Trie<maxn> trie;

void solve() {
    int N; cin >> N;
    
    vector<int> arr(N);
    for (auto &x : arr) cin >> x;
    sort(ALL(arr)), arr.resize(unique(ALL(arr)) - begin(arr));
    N = arr.size();
    
    for (auto &x : arr) trie.Insert(x);
    cout << trie.recur(0, 30) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        solve();
    }
    
    return 0;
}