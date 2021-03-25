#pragma GCC optimize("Ofast", "unroll-loops")
#include "Anna.h"
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

vector<int> compress(vector<int> v) {
    initialize();
    v.resize(v.size() + (ENC - v.size() % ENC) % ENC, 0);
    vector<int> ret(v.size() / ENC * DEC, 0);
    for (int i = 0, p = 0; i < v.size(); i += ENC, p += DEC) {
        int64_t num = 0;
        for (int j = 0, k = ENC-1; j < ENC; ++j, --k) num += v[i+j] * fib[k];
        for (int j = 0, k = DEC-1; j < DEC; ++j, --k) ret[p+j] = num >> k & 1;
    }
    return ret;
}

} // namespace

void Anna(int N, vector<char> S) {
    int flag = -1;
    vector<int> vec(N, 0);
    for (int i = 0; i < N; ++i) {
        if (S[i] == 'X' and flag == -1) flag = i;
        if (S[i] == 'Z' and flag != -1) vec[i] = 1;
        if (i and vec[i-1] and vec[i]) vec[i-1] = 0;
    }
    // cerr << "Original:   "; for (auto x : vec) cerr << x; cerr << "\n";
    vec = compress(vec);
    // cerr << "Compress:   "; for (auto x : vec) cerr << x; cerr << "\n";
    for (int i = 0; i < 20; ++i) vec.eb(flag >> i & 1);
    for (auto x : vec) Send(x);
}

/*
4 X Y X Z
7 X Y X Y Z Y Z
13 X Y Z Y X Z Y Y X Z X Y Z
10 Y Y Y Y Y Y Y Y Y Y
*/