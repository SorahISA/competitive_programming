#include <bits/stdc++.h>
using namespace std;

#define int long long
#define double long double
using pii = pair<int, int>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using Prior = std::priority_queue<T>;

#define X first
#define Y second
#define eb emplace_back
#define ef push_front
#define pb pop_back
#define pf pop_front
#define SZ(x) (int)(x).size()
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

template<typename T> bool chmin(T &lhs, T rhs) {return lhs > rhs ? lhs = rhs, 1 : 0;}
template<typename T> bool chmax(T &lhs, T rhs) {return lhs < rhs ? lhs = rhs, 1 : 0;}

const int maxn = 1 << 16;
const int maxp = 35;

const int primes[] = {  2,   3,   5,   7,  11,  13,  17,
                       19,  23,  29,  31,  37,  41,  43,
                       47,  53,  59,  61,  67,  71,  73,
                       79,  83,  89,  97, 101, 103, 107,
                      109, 113, 127, 131, 137, 139, 149};

namespace SegTree {

int sum[maxp][maxn<<1], tag[maxp][maxn<<1];

void Pull(int id, int now) {
    sum[id][now] = sum[id][now<<1] + sum[id][now<<1|1];
}

void Push(int id, int now, int len) {
    if (!tag[id][now]) return;
    tag[id][now<<1]   += tag[id][now];
    tag[id][now<<1|1] += tag[id][now];
    sum[id][now<<1]   += tag[id][now] * (len / 2);
    sum[id][now<<1|1] += tag[id][now] * (len / 2);
    tag[id][now] = 0;
}

void RangeAdd(int id, int qL, int qR, int val, int now = 1, int nL = 0, int nR = maxn-1) {
    if (qR < nL or nR < qL) return;
    if (qL <= nL and nR <= qR) {
        tag[id][now] += val;
        sum[id][now] += (nR - nL + 1) * val;
        return;
    }
    
    Push(id, now, nR - nL + 1);
    int nM = (nL + nR) >> 1;
    RangeAdd(id, qL, qR, val, now << 1    , nL,     nM);
    RangeAdd(id, qL, qR, val, now << 1 | 1, nM + 1, nR);
    Pull(id, now);
}

int RangeSum(int id, int qL, int qR, int now = 1, int nL = 0, int nR = maxn-1) {
    if (qR < nL or nR < qL) return 0;
    if (qL <= nL and nR <= qR) return sum[id][now];
    
    Push(id, now, nR - nL + 1);
    int ans = 0, nM = (nL + nR) >> 1;
    ans += RangeSum(id, qL, qR, now << 1    , nL,     nM);
    ans += RangeSum(id, qL, qR, now << 1 | 1, nM + 1, nR);
    Pull(id, now);
    return ans;
}

};

int mypow(int base, int exp, int mod, int ans = 1) {
    while (exp) {
        if (exp & 1) ans = ans * base % mod;
        base = base * base % mod, exp >>= 1;
    }
    return ans;
}

void solve() {
    using namespace SegTree;
    
    int N, M; cin >> N >> M;
    
    int op, L, R, V;
    while (M--) {
        cin >> op >> L >> R >> V;
        
        vector<int> qry(maxp, 0);
        if (op != 0) {
            for (int i = 0; i < maxp; ++i) {
                while (V % primes[i] == 0) ++qry[i], V /= primes[i];
            }
        }
        
        int ans = 1;
        if (L <= R) {
            for (int i = 0; i < maxp; ++i) {
                if (op == 0) ans = ans * mypow(primes[i], RangeSum(i, L, R), V) % V;
                if (op == 1) RangeAdd(i, L, R,  qry[i]);
                if (op == 2) RangeAdd(i, L, R, -qry[i]);
            }
        }
        else {
            for (int i = 0; i < maxp; ++i) {
                if (op == 0) ans = ans * mypow(primes[i], RangeSum(i, L, N), V) % V
                                       * mypow(primes[i], RangeSum(i, 1, R), V) % V;
                if (op == 1) RangeAdd(i, L, N,  qry[i]), RangeAdd(i, 1, R,  qry[i]);
                if (op == 2) RangeAdd(i, L, N, -qry[i]), RangeAdd(i, 1, R, -qry[i]);
            }
        }
        if (op == 0) cout << ans << "\n";
    }
}

void init() {
    using namespace SegTree;
    memset(sum, 0x00, sizeof(sum));
    memset(tag, 0x00, sizeof(tag));
}

int32_t main() {
    fastIO();
    
    int t = 1; cin >> t;
    for (int _ = 1; _ <= t; ++_) {
        init(), solve();
    }
    
    return 0;
}
