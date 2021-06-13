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
const int maxn = 32 * (int)4E5 + 5;
// const int maxn = 32 * (int)40 + 5;

struct Trie {
    int cnt, sub[2];
    
    Trie() {
        cnt = 0;
        sub[0] = sub[1] = -1;
    }
} trie[maxn];

void InsertTrie(int x) {
    static int tok = 0;
    int now = 0;
    for (int i = 31; i >= 0; --i) {
        if (trie[now].sub[x>>i&1] == -1) trie[now].sub[x>>i&1] = ++tok;
        ++trie[now].cnt, now = trie[now].sub[x>>i&1];
    }
    ++trie[now].cnt;
}

int CheckAnswer(int idx) {
    /// trie[trie[idx].sub[0]] is a trie and we need to find ///
    /// minimum XOR for every node in trie[trie[idx].sub[1]] ///
    
    int ans = INF;
    deque<int> deq0{trie[idx].sub[0]}, deq1{trie[idx].sub[1]}, val{1};
    while (!deq1.empty()) {
        int now0 = deq0.back(), now1 = deq1.back(), nval = val.back(), fl = 0;
        deq0.pb(), deq1.pb(), val.pb();
        for (int i : {0, 1}) {
            if (trie[now0].sub[i] != -1) {
                fl = 1;
                deq0.eb(trie[now0].sub[i]);
                if (trie[now1].sub[i] != -1) deq1.eb(trie[now1].sub[i]),   val.eb(nval << 1);
                else                         deq1.eb(trie[now1].sub[i^1]), val.eb(nval << 1 | 1);
            }
        }
        if (fl == 0) ans = min(ans, nval);
    }
    return ans;
}

int BfsTrie(int st, int fl, int &maxBit) {
    deque<pii> deq{{st, 32}}; /// (id, hei)
    int ans = 0;
    while (!deq.empty()) {
        auto [now, hei] = deq.front(); deq.pf();
        if (trie[now].sub[1] != -1 and trie[trie[now].sub[1]].cnt & 1) {
            if (fl == 0) maxBit = max(hei, maxBit);
            if (fl == 1 and hei == maxBit) ans = max(ans, CheckAnswer(now));
            continue;
        }
        if (trie[now].sub[0] != -1) deq.eb(trie[now].sub[0], hei - 1);
        if (trie[now].sub[1] != -1) deq.eb(trie[now].sub[1], hei - 1);
    }
    return ans;
}

void solve() {
    int N; cin >> N;
    
    vector<int> arr(2*N);
    for (auto &x : arr) cin >> x, InsertTrie(x);
    
    int maxBit = 0;
    BfsTrie(0, 0, maxBit);
    cout << BfsTrie(0, 1, maxBit) << "\n";
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