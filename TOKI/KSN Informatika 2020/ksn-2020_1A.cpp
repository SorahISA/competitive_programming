#pragma GCC optimize("Ofast", "unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
template<typename T>
using Prior = std::priority_queue<T>;
template<typename T>
using prior = std::priority_queue<T, vector<T>, greater<T>>;

#define X first
#define Y second
#define eb emplace_back
#define ALL(x) begin(x), end(x)
#define RALL(x) rbegin(x), rend(x)
#define fastIO() ios_base::sync_with_stdio(0), cin.tie(0)

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int getRand(int L, int R) {
    if (L > R) swap(L, R);
    return (int)(rng() % (uint64_t)(R - L + 1) + L);
}

ifstream& operator >> (ifstream &is, vector<int> &vec) {
    for (auto &x : vec) is >> x;
    return is;
}

ifstream fin;
ofstream fout;

int N, M, K;
vector<int> A;

void solve01() {
    
    /*
     * N = 5; M = 5; A = [4, 4, 4, 4, 9]
     *
     * ....x
     * x***x
     * x***x
     * x***x
     * x....
     */
    
    fout << 0 << " " << 1 << " " << 0 << " " << 4 << "\n";
    fout << 0 << " " << 4 << " " << 4 << " " << 5 << "\n";
    fout << 4 << " " << 5 << " " << 1 << " " << 5 << "\n";
    fout << 1 << " " << 5 << " " << 0 << " " << 1 << "\n";
    fout << 1 << " " << 4 << " " << 1 << " " << 4 << "\n";
}

void solve02() {
    
    /*
     * N = 6; M = 7; A = [2, 3, 4, 5, 6, 6, 7, 9]
     *
     * GDDDDD
     * GHHHEF
     * GHHHEF
     * GHHHEF
     * GCCBEF
     * GCCBEF
     * GAABEF
     */
    
    fout << 1 << " " << 3 << " " << 0 << " " << 1 << "\n";
    fout << 3 << " " << 4 << " " << 0 << " " << 3 << "\n";
    fout << 1 << " " << 3 << " " << 1 << " " << 3 << "\n";
    fout << 1 << " " << 6 << " " << 6 << " " << 7 << "\n";
    fout << 4 << " " << 5 << " " << 0 << " " << 6 << "\n";
    fout << 5 << " " << 6 << " " << 0 << " " << 6 << "\n";
    fout << 0 << " " << 1 << " " << 0 << " " << 7 << "\n";
    fout << 1 << " " << 4 << " " << 3 << " " << 6 << "\n";
}

void solve03() {
    
    /// N = 1; M = 10^9; K = 10^5 ///
    
    int sum = 0;
    for (auto x : A) {
        fout << 0 << " " << 1 << " " << sum << " ";
        sum += x;
        fout << sum << "\n";
    }
}

void solve04() {
    
    /// N = 99999; M = 50000; K = 99999; A = [1, 2, 3, ..., 99999] ///
    
    for (int i = 1; i <= 49999; ++i) {
        fout << 0 << " " << i << " " << i << " " << i+1 << "\n";
    }
    for (int i = 49999; i >= 0; --i) {
        fout << i << " " << N << " " << i << " " << i+1 << "\n";
    }
}

void solve05() {
    
    /// N = 9973 * 293; M = 99991 * 311; K = 293 * 311; A = [9973 * 99991, ..., 9973 * 99991] ///
    
    for (int i = 0; i < 293; ++i) {
        for (int j = 0; j < 311; ++j) {
            fout << 9973*i << " " << 9973*(i+1) << " " << 99991*j << " " << 99991*(j+1) << "\n";
        }
    }
}

void solve06() {
    
    /// N = 2; M = 10^9; K = 20 ///
    
    vector<int> state(K, -1), tmp_state(K, -1);
    
    function<void(int, int, int, int)> dfs = [&](int now, int sum1, int sum2, int right) {
        if (sum1 > right or sum2 > right) return;
        if (now == K) return state = tmp_state, void();
        tmp_state[now] = 0;
        dfs(now + 1, sum1 + A[now], sum2, right);
        tmp_state[now] = 1;
        dfs(now + 1, sum1, sum2 + A[now], right);
        if (~A[now] & 1) {
            tmp_state[now] = 2;
            dfs(now + 1, sum1, sum2, right - A[now] / 2);
        }
    };
    dfs(0, 0, 0, M);
    
    vector<tuple<int, int, int, int>> answer(K);
    int sum1 = 0, sum2 = 0, right = M;
    
    for (int i = 0; i < K; ++i) {
             if (state[i] == 0) answer[i] = {0, 1, sum1, sum1 + A[i]}, sum1 += A[i];
        else if (state[i] == 1) answer[i] = {1, 2, sum2, sum2 + A[i]}, sum2 += A[i];
        else if (state[i] == 2) answer[i] = {0, 2, right - A[i]/2, right}, right -= A[i]/2;
    }
    
    for (auto [x1, x2, y1, y2] : answer) fout << x1 << " " << x2 << " " << y1 << " " << y2 << "\n";
}

void solve07() {
    
    /// N = 2; M = 10000; K = 100 ///
    
    for (int i = 0; i < K; ++i) {
        if (A[i] % 2 == 0) A[i] /= 2, A.eb(A[i]);
        else A.eb(0);
    }
    
    bitset<10001> dp[2*K];
    dp[0][0] = dp[0][A[0]] = 1;
    for (int i = 1; i < 2*K; ++i) dp[i] = dp[i-1] | dp[i-1] << A[i];
    
    bitset<200> choosed;
    for (int i = 2*K-1, p = M; i >= 0 and p > 0; --i) {
        if (i and p >= A[i] ? dp[i-1][p-A[i]] : (p == A[i])) choosed[i] = 1, p -= A[i];
    }
    
    for (int i = 0, sum1 = 0, sum2 = 0, right = M; i < K; ++i) {
        if (choosed[i] == 0 and (A[K+i] == 0 or choosed[K+i] == 0)) {
            fout << 0 << " " << 1 << " " << sum1 << " " << sum1 + A[i] + A[K+i] << "\n";
            sum1 += A[i] + A[K+i];
        }
        else if (choosed[i] == 1 and (A[K+i] == 0 or choosed[K+i] == 1)) {
            fout << 1 << " " << 2 << " " << sum2 << " " << sum2 + A[i] + A[K+i] << "\n";
            sum2 += A[i] + A[K+i];
        }
        else if (choosed[i] != choosed[K+i]) {
            fout << 0 << " " << 2 << " " << right - A[i] << " " << right << "\n";
            right -= A[i];
        }
    }
}

void solve08() {
    
    /// N = 4681; M = 229383; A = [1, 2, 4, 8, ..., 2^29] ///
    
    vector<tuple<int, int, int, int>> answer(K);
    answer[29] = {     0, 131072,    0, 4096};
    answer[28] = {131072, 196608,    0, 4096};
    answer[27] = {196608, 229376,    0, 4096};
    answer[26] = {     0, 131072, 4096, 4608};
    answer[25] = {131072, 196608, 4096, 4608};
    answer[24] = {196608, 229376, 4096, 4608};
    answer[23] = {     0, 131072, 4608, 4672};
    answer[22] = {131072, 196608, 4608, 4672};
    answer[21] = {196608, 229376, 4608, 4672};
    answer[20] = {     0, 131072, 4672, 4680};
    answer[19] = {131072, 196608, 4672, 4680};
    answer[18] = {196608, 229376, 4672, 4680};
    answer[17] = {     0, 131072, 4680, 4681};
    answer[16] = {131072, 196608, 4680, 4681};
    answer[15] = {196608, 229376, 4680, 4681};
    
    answer[14] = {229376, 229380,    0, 4096};
    answer[13] = {229380, 229382,    0, 4096};
    answer[12] = {229382, 229383,    0, 4096};
    answer[11] = {229376, 229380, 4096, 4608};
    answer[10] = {229380, 229382, 4096, 4608};
    answer[ 9] = {229382, 229383, 4096, 4608};
    answer[ 8] = {229376, 229380, 4608, 4672};
    answer[ 7] = {229380, 229382, 4608, 4672};
    answer[ 6] = {229382, 229383, 4608, 4672};
    answer[ 5] = {229376, 229380, 4672, 4680};
    answer[ 4] = {229380, 229382, 4672, 4680};
    answer[ 3] = {229382, 229383, 4672, 4680};
    answer[ 2] = {229376, 229380, 4680, 4681};
    answer[ 1] = {229380, 229382, 4680, 4681};
    answer[ 0] = {229382, 229383, 4680, 4681};
    
    for (auto [y1, y2, x1, x2] : answer) fout << x1 << " " << x2 << " " << y1 << " " << y2 << "\n";
}

void solve09() {
    
    /// N = 46368 = F(21) + F(22); M = 28657 = F(22); K = 23 ///
    /// A = [F(0)^2, F(1)^2, F(2)^2, ..., F(22)^2] ///
    
    vector<int> F(23, 0); F[1] = 1;
    for (int i = 2; i <= 22; ++i) F[i] = F[i-1] + F[i-2];
    
    vector<tuple<int, int, int, int>> answer;
    for (int i = 22; i >= 0; --i) {
        if (N > M) answer.eb(N-M, N,   0, M), N -= M;
        else       answer.eb(  0, N, M-N, M), M -= N;
    }
    reverse(ALL(answer));
    
    for (auto [x1, x2, y1, y2] : answer) fout << x1 << " " << x2 << " " << y1 << " " << y2 << "\n";
}

void solve10() {
    
    /// N = 2000; M = 2000; K = 79191; Ai <= 100 ///
    /// N = 2000; M = 2000; K = 78987; Ai <= 100 ///
    
    int tok = 0;
    vector<tuple<int, int, int, int>> answer(K);
    vector<int> sum(N, 0);
    set<pii> st;
    for (int i = 0; i < K; ++i) st.insert({A[i], i});
    
    while (!st.empty()) {
        auto p = st.lower_bound({M - sum[tok], 1000000});
        if (p != st.begin()) p = prev(p);
        else {assert(0); ++tok; continue;}
        answer[p->Y] = {tok, tok + 1, sum[tok], sum[tok] + p->X}, sum[tok] += p->X;
        if (sum[tok] == M) ++tok;
        st.erase(p);
    }
    
    for (auto [x1, x2, y1, y2] : answer) fout << x1 << " " << x2 << " " << y1 << " " << y2 << "\n";
}

int main() {
    fastIO();
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("inputs/01.in");
    // fout = ofstream("outputs/01.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve01(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("inputs/02.in");
    // fout = ofstream("outputs/02.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve02(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("inputs/03.in");
    // fout = ofstream("outputs/03.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve03(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("ksn-inputs/pertahanan_3.in");
    // fout = ofstream("outputs/pertahanan_3.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve03(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("inputs/04.in");
    // fout = ofstream("outputs/04.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve04(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("inputs/05.in");
    // fout = ofstream("outputs/05.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve05(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("inputs/06.in");
    // fout = ofstream("outputs/06.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve06(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("ksn-inputs/pertahanan_6.in");
    // fout = ofstream("outputs/pertahanan_6.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve06(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("inputs/07.in");
    // fout = ofstream("outputs/07.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve07(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("ksn-inputs/pertahanan_7.in");
    // fout = ofstream("outputs/pertahanan_7.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve07(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("inputs/08.in");
    // fout = ofstream("outputs/08.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve08(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("inputs/09.in");
    // fout = ofstream("outputs/09.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve09(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("inputs/10.in");
    // fout = ofstream("outputs/10.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve10(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    /// ============ CASE CLOSED ============ ///
    // fin = ifstream("ksn-inputs/pertahanan_10.in");
    // fout = ofstream("outputs/pertahanan_10.out");
    // fin >> N >> M >> K, A.resize(K), fin >> A;
    // solve10(), fin.close(), fout.close();
    /// ============ CASE CLOSED ============ ///
    
    
    return 0;
}