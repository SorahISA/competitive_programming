#pragma GCC optimize("Ofast", "unroll-loops")
#include <cstdio>
#include <algorithm>
using namespace std;

#define X first
#define Y second

// #define getchar_unlocked getchar
// #define putchar_unlocked putchar

const int INF = 1E9;
const int fact_10 = 3628800 + 5;
const int maxq = 1E6 + 5;
const int maxn = 10 + 5;
const int S = 1 << 16;

int A[maxn], ans[maxq], all_score[fact_10];
int N, M, Q, i, tok, score, all_score_sz = 0;
long long qs;
pair<int, int> query[maxq];

/// Fast I/O by FHVirus ///
/// https://fhvirus.github.io/blog/2020/fhvirus-io/ ///

char OB[S];
int OP, _OP;

inline char RC() {
    // static char buf[S], *p = buf, *q = buf;
    // return p == q and (q = (p = buf) + read(0, buf, S)) == buf ? -1 : *p++;
    return getchar_unlocked();
}

inline int RI() {
    static char c;
    int a;
    while (((c = RC()) < '0' or c > '9') and c != '-' and c != -1);
    if (c == '-') {
        a = 0;
        while ((c = RC()) >= '0' and c <= '9') a *= 10, a -= c ^ '0';
    }
    else {
        a = c ^ '0';
        while ((c = RC()) >= '0' and c <= '9') a *= 10, a += c ^ '0';
    }
    return a;
}

inline long long RL() {
    static char c;
    long long a;
    while (((c = RC()) < '0' or c > '9') and c != '-' and c != -1);
    if (c == '-') {
        a = 0;
        while ((c = RC()) >= '0' and c <= '9') a *= 10, a -= c ^ '0';
    }
    else {
        a = c ^ '0';
        while ((c = RC()) >= '0' and c <= '9') a *= 10, a += c ^ '0';
    }
    return a;
}

inline void WI(int n) {
    static char buf[12], p;
    if (n == 0) OB[OP++] = '0';
    p = 0;
    if (n < 0) {
        OB[OP++] = '-';
        while (n) buf[p++] = '0' - (n % 10), n /= 10;
    }
    else {
        while (n) buf[p++] = '0' + (n % 10), n /= 10;
    }
    for (--p; p >= 0; --p) OB[OP++] = buf[p];
    OB[OP++] = '\n';
    if (OP > S-30) {
        // fwrite(OB, 1, OP, stdout);
        for (_OP = 0; _OP < OP; ++_OP) putchar_unlocked(OB[_OP]);
        OP = 0;
    }
}

/// Fast I/O by FHVirus ///
/// https://fhvirus.github.io/blog/2020/fhvirus-io/ ///

int main() { /// ZeroJudge c272
    
    N = RI(), M = RI(), Q = RI();
    for (i = 0; i < N; ++i) A[i] = RI();
    sort(A, A + N);
    
    do {
        for (i = score = 0; i < M; ++i) score += A[i] * (M - i);
        all_score[all_score_sz++] = score;
    } while (next_permutation(A, A + N));
    all_score[all_score_sz++] = INF;
    sort(all_score, all_score + all_score_sz);
    
    for (i = 0; i < Q; ++i) {
        qs = RL();
        if (qs < all_score[0]) qs = all_score[0] - 1;
        query[i].X = qs, query[i].Y = i;
    }
    sort(query, query + Q);
    
    for (i = 0, tok = 0; i < Q; ++i) {
        if (query[i].X < all_score[0]) {
            ans[query[i].Y] = -1; continue;
        }
        while (all_score[tok+1] <= query[i].X) ++tok;
        ans[query[i].Y] = tok;
    }
    
    for (i = 0; i < Q; ++i) {
        // cout << "Case #" << i+1 << "\n";
        OB[OP++] = 'C', OB[OP++] = 'a', OB[OP++] = 's', OB[OP++] = 'e';
        OB[OP++] = ' ', OB[OP++] = '#', WI(i+1);
        if (ans[i] != -1) WI(all_score[ans[i]]);
        else {
            // cout << "No Solution!\n";
            OB[OP++] = 'N', OB[OP++] = 'o', OB[OP++] = ' ';
            OB[OP++] = 'S', OB[OP++] = 'o', OB[OP++] = 'l', OB[OP++] = 'u';
            OB[OP++] = 't', OB[OP++] = 'i', OB[OP++] = 'o', OB[OP++] = 'n';
            OB[OP++] = '!', OB[OP++] = '\n';
        }
    }
    if (OP) {
        // fwrite(OB, 1, OP, stdout);
        for (_OP = 0; _OP < OP; ++_OP) putchar_unlocked(OB[_OP]);
        OP = 0;
    }
    
    return 0;
}