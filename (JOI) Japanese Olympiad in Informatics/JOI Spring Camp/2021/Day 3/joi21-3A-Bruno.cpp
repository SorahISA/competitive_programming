#pragma GCC optimize("Ofast", "unroll-loops")
#include "Bruno.h"
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

namespace {

const int ENC = 63;
const int DEC = 44;

int64_t fib[ENC];

void initialize() {
    fib[0] = 1, fib[1] = 2;
    for (int i = 2; i < ENC; ++i) fib[i] = fib[i-1] + fib[i-2];
}

vector<int> decompress(vector<int> v) {
    initialize();
    vector<int> ret(v.size() * ENC / DEC, 0);
    for (int i = 0, p = 0; i < v.size(); i += DEC, p += ENC) {
        int64_t num = 0;
        for (int j = 0, k = DEC-1; j < DEC; ++j, --k) num |= (int64_t)v[i+j] << k;
        for (int j = 0, k = ENC-1; j < ENC; ++j, --k) ret[p+j] = num >= fib[k], num %= fib[k];
    }
    return ret;
}

} // namespace

void Bruno(int N, int L, vector<int> A) {
    int lst = 0;
    for (int i = 0; i < 20; ++i) lst |= A[A.size()-20+i] << i;
    if (lst >= N) lst = -1;
    A.resize(A.size() - 20);
    // cerr << "Receive:    "; for (auto x : A) cerr << x; cerr << "\n";
    A = decompress(A), A.resize(N);
    // cerr << "Decompress: "; for (auto x : A) cerr << x; cerr << "\n";
    
    vector<int> tok(N, 1);
    for (int i = 0; i < N; ++i) {
        if (A[i] == 1 and lst == -1) lst = i;
        else if (A[i] == 1) {
            for (int j = i-1; j > lst; --j) tok[j] = 0, Remove(j);
            tok[i] = 0, Remove(i), lst = i;
        }
    }
    for (int i = 0; i < N; ++i) if (tok[i]) Remove(i);
}
