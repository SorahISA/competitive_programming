#ifdef local
#define _GLIBCXX_DEBUG 1
#endif
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define double __float80
using pii = pair<int,int>;
template <typename T> using MaxHeap = priority_queue<T>;
template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

#define SZ(a) (int)((a).size())
#define ALL(a) begin(a), end(a)
#define RALL(a) rbegin(a), rend(a)
#define ee emplace
#define eb emplace_back
#define ef emplace_front
#define pb pop_back
#define pf pop_front
// #define X first
// #define Y second

template <typename U, typename V> bool chmin(U &u, V v) {return u > v ? u = v, 1 : 0;}
template <typename U, typename V> bool chmax(U &u, V v) {return u < v ? u = v, 1 : 0;}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int K;
vector<vector<int>> A, inv, pre;
vector<int> par;

void recur(vector<int> L, vector<int> R, int fa = -1) {
    if (L[0] == R[0]) return par[ A[0][L[0]] ] = fa, void();
    for (int rt = L[0]+1; rt <= R[0]-1; rt += 2) {
        int hash_L = (pre[0][rt] ^ pre[0][L[0]-1]), hash_R = (pre[0][R[0]] ^ pre[0][rt-1]);
        int flag = true;
        for (int i = 1; i < K and flag; ++i) {
            int tmp_L = (pre[i][inv[i][ A[0][rt] ]] ^ pre[i][L[i]-1]);
            int tmp_R = (pre[i][R[i]] ^ pre[i][inv[i][ A[0][rt] ]-1]);
            if (
                    (hash_L == tmp_L and hash_R == tmp_R)
                or  (hash_L == tmp_R and hash_R == tmp_L)
            );
            else flag = false;
        }
        if (flag) {
            par[ A[0][rt] ] = fa;
            vector<int> L1, R1, L2, R2;
            for (int i = 0; i < K; ++i) {
                int tmp_L = (pre[i][inv[i][ A[0][rt] ]] ^ pre[i][L[i]-1]);
                int tmp_R = (pre[i][R[i]] ^ pre[i][inv[i][ A[0][rt] ]-1]);
                if (hash_L == tmp_L and hash_R == tmp_R) {
                    L1.eb(L[i]), R1.eb(inv[i][ A[0][rt] ]-1);
                    L2.eb(inv[i][ A[0][rt] ]+1), R2.eb(R[i]);
                }
                else {
                    L1.eb(inv[i][ A[0][rt] ]+1), R1.eb(R[i]);
                    L2.eb(L[i]), R2.eb(inv[i][ A[0][rt] ]-1);
                }
            }
            recur(L1, R1, A[0][rt]);
            recur(L2, R2, A[0][rt]);
            break;
        }
    }
}

void solve() {
    int N; cin >> N >> K;
    
    A.assign(K, vector<int>(N+1, 0));
    inv.assign(K, vector<int>(N+1, 0));
    for (int i = 0; i < K; ++i) {
        for (int j = 1; j <= N; ++j) cin >> A[i][j], inv[i][A[i][j]] = j;
    }
    
    vector<int> H(N+1);
    for (int &x : H) x = rng();
    
    pre = A;
    for (auto &vec : pre) {
        int lst = 0;
        for (int &x : vec) lst = x = lst ^ H[x];
    }
    
    par.assign(N+1, -2);
    vector<int> L(K, 1), R(K, N);
    recur(L, R);
    
    for (int i = 1; i <= N; ++i) cout << par[i] << " \n"[i == N];
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t = 1; // cin >> t;
    for (int i = 1; i <= t; ++i) solve();
    return 0;
}
