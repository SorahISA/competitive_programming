// #pragma GCC optimize("Ofast", "unroll-loops")
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

const int maxn = 1E6 + 5;
const int maxsigma = 26;

template<size_t sz, size_t sigma>
struct ACautomaton {
    int cnt[sz], sub[sz][sigma], fail[sz], tok;
    
    ACautomaton() {Init();}
    
    void Init() {
        memset(cnt, 0x00, sizeof(cnt));
        memset(sub, 0x00, sizeof(sub));
        memset(fail, 0x00, sizeof(fail));
        tok = 0;
    }
    
    void Insert(const string &str) {
        int now = 0;
        for (auto c : str) {
            int p = c - 'a';
            if (!sub[now][p]) sub[now][p] = ++tok;
            now = sub[now][p];
        }
        ++cnt[now];
    }
    
    void BuildFail() {
        deque<int> deq;
        for (int i = 0; i < sigma; ++i) if (sub[0][i]) deq.eb(sub[0][i]);
        while (!deq.empty()) {
            int now = deq.front(); deq.pf();
            for (int i = 0; i < sigma; ++i) {
                if (sub[now][i]) fail[sub[now][i]] = sub[fail[now]][i], deq.eb(sub[now][i]);
                else sub[now][i] = sub[fail[now]][i];
            }
        }
    }
    
    int Query(const string &str) {
        int now = 0, ans = 0, p;
        for (auto c : str) {
            p = now = sub[now][c-'a'];
            while (p and cnt[p] != -1) ans += cnt[p], cnt[p] = -1, p = fail[p];
        }
        return ans;
    }
    
    void Print() {
        for (int i = 0; i <= tok; ++i) {
            cout << i << ": ";
            for (int j = 0; j < sigma; ++j) {
                if (sub[i][j]) cout << "(" << sub[i][j] << "," << (char)('a'+j) << ")";
            }
            cout << " | " << fail[i] << "\n";
        }
    }
};

ACautomaton<maxn, maxsigma> acam;

void solve() {
    int N; cin >> N;
    
    vector<string> vec(N);
    for (auto &str : vec) cin >> str, acam.Insert(str);
    acam.BuildFail();
    // acam.Print();
    
    string T; cin >> T;
    cout << acam.Query(T) << "\n";
}

int32_t main() {
    fastIO();
    
    int t = 1; // cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        // cout << "Case #" << _ << ": ";
        acam.Init(), solve();
    }
    
    return 0;
}